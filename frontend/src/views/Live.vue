<template>
    <VContainer align="center" fluid color="surface">

        <div class="sep">
        <VRow max-width="1200px">
            <!-- Row 1-->
            <VCol cols="9">
                <!-- Row 1 column 1-->
                <figure class="highcharts-fugure">
                    <div id="container"></div>
                </figure>
            </VCol>


            <VCol cols="3">
                <!-- Row 1 column 2-->
                <v-card class="mb-5 circle-card" max-width="300" color="primaryContainer">
                    <!-- Card 1, temperature-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Temperature</div>
                        <VCardItem class="card-value">
                            <span class="text-h3 text-onPrimaryContainer">{{ temperature }}</span>
                        </VCardItem>
                    </VCardText>
                </v-card>

                <v-card class="mb-5 circle-card" max-width="500" color="tertiaryContainer">
                    <!-- Card 2, heat index-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Heat Index</div>
                        <VCardItem>
                            <span class="text-h3 text-onTertiaryContainer">{{ heatindex }}</span>
                        </VCardItem>

                    </VCardText>
                    
                </v-card>
                
                <v-btn 
        @click="useFahrenheit = !useFahrenheit"
        color="primary"
        class="mb-4"
        block
    >
        {{ `Switch to ${useFahrenheit ? 'Celsius' : 'Fahrenheit'}` }}
    </v-btn>
                
               
                
            </VCol>
        </VRow>
    </div>

    <div class="sep">
        <VRow max-width="1200px" justify="start">
            <!-- Row 2-->
            <VCol cols="9">
                <!-- Row 2 column 1-->
                <figure class="highcharts-fugure">
                    <div id="container1"></div>
                </figure>
            </VCol>

            <VCol cols="3">
                <!-- Row 2 column 2-->
                <v-card class="mb-5 circle-card" max-width="500" color="secondaryContainer">
                    <!-- Card 3, humidity-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Humidity</div>
                        <VCardItem>
                            <span class="text-h3 text-onSecondaryContainer">{{ humidity }}</span>
                        </VCardItem>

                    </VCardText>
                    
                </v-card>
            </VCol>
        </VRow>
    </div>
    <div class="sep">
        <VRow max-width="1200px" justify="start">
            <!-- Row 3-->
             <VCol cols="9">
               <!-- Row 3 column 1--> 
               <figure class="highcharts-figure">
                    <div id="container2">
                        <!-- pressure graph -->
                    </div>
                </figure>
             </VCol>
             <VCol cols="3">
                <!-- Row 3 column 2-->
                <v-card class="mb-5 circle-card" max-width="500" color="secondaryContainer" >
                    <!-- Card 4, pressure-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Pressure</div>
                        <VCardItem>
                            <span class="text-h3 text-onSecondaryContainer">{{ pressure }}</span>
                        </VCardItem>
                    </VCardText>
                    
                </v-card>

            </VCol>

        </VRow>
    </div>
    <div class="sep">
        <VRow max-width="1200px" justify="start">
            <!-- Row 4-->
             <VCol cols="9">
               <!-- Row 4 column 1--> 
               <figure class="highcharts-figure">
                    <div id="container3">
                        <!-- altitude graph -->
                    </div>
                </figure>
             </VCol>
             <VCol cols="3">
                <!-- Row 4 column 2-->
                <v-card class="mb-5 circle-card" max-width="500" color="secondaryContainer" >
                    <!-- Card 5, altitude-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Altitude</div>
                        <VCardItem>
                            <span class="text-h3 text-onSecondaryContainer">{{ altitude }}</span>
                        </VCardItem>


                    </VCardText>
                    
                </v-card>
            </VCol>
        </VRow>
    </div>
    <div class="sep">
        <VRow max-width="1200px" justify="start">
            <!-- Row 5-->
             <VCol cols="9">
               <!-- Row 5 column 1--> 
               <figure class="highcharts-figure">
                    <div id="container4">
                        <!-- moisture graph -->
                    </div>
                </figure>
             </VCol>

             <VCol cols="3">
                <!-- Row 5 column 2-->
                <v-card class="mb-5 circle-card" max-width="500" color="secondaryContainer" >
                    <!-- Card 6, moisture-->
                    <VCardText class="card-content">
                        <div class="text-subtitle-1 text-center card-subtitle">Moisture</div>
                        <VCardItem>
                            <span class="text-h3 text-onSecondaryContainer">{{ moisture }}</span>
                        </VCardItem>
                    </VCardText>
                    
                </v-card>
            </VCol>

        </VRow>
    </div>
    </VContainer>
</template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS




// Highcharts, Load the exporting module and Initialize exporting module. 
import { ref, reactive, watch, onMounted, onBeforeUnmount, computed } from "vue";  
import { useRoute, useRouter } from "vue-router";
import { useMqttStore } from '@/store/mqttStore'; 
import { storeToRefs } from "pinia"; 
import { useAppStore } from "@/store/appStore"; 
import Highcharts from 'highcharts'; 
import more from 'highcharts/highcharts-more'; 
import Exporting from 'highcharts/modules/exporting'; 
Exporting(Highcharts);  
more(Highcharts);

// VARIABLES 
const Mqtt = useMqttStore(); 
const { payload, payloadTopic } = storeToRefs(Mqtt);
const router = useRouter();
const route = useRoute();  
const AppStore = useAppStore(); 
const tempHiChart = ref(null); 
const humidHiChart = ref(null);
const pressureHiChart = ref(null);
const altitudeHiChart = ref(null);
const moistureHiChart = ref(null);
const useFahrenheit = ref(false);
const tempUnit = computed(() => useFahrenheit.value ? '°F' : '°C');
const points = ref(10); 
const shift = ref(false); 

// Reactive object to hold latest data
const latestData = reactive({
  temperature: null,
  heatindex: null,
  humidity: null,
  pressure: null,
  altitude: null,
  moisture: null,
  timestamp: null,
});

let refreshTimeout = null;

// Reset timeout on data received
const resetRefreshTimeout = () => {
  if (refreshTimeout) clearTimeout(refreshTimeout);
  refreshTimeout = setTimeout(() => {
    // Reset data to 0
    Object.keys(latestData).forEach(key => {
      latestData[key] = 0;
    });
    // Clear charts
    clearAllCharts();
  }, 10000);
};

// Clear all chart data
const clearAllCharts = () => {
  const charts = [
    tempHiChart.value,
    humidHiChart.value,
    pressureHiChart.value,
    altitudeHiChart.value,
    moistureHiChart.value,
  ];
  charts.forEach(chart => {
    if (chart) {
      chart.series.forEach(series => {
        series.setData([]);
      });
    }
  });
};

// Computed properties using latestData
const temperature = computed(() => { 
  if (latestData.temperature !== null) { 
    const temp = useFahrenheit.value ? (latestData.temperature * 9/5 + 32) : latestData.temperature;
    return `${temp.toFixed(2)} ${tempUnit.value}`; 
  } 
  return '--';
});

const humidity = computed(() => { 
  if (latestData.humidity !== null) { 
    return `${latestData.humidity.toFixed(2)}%`; 
  } 
  return '--';
});

const heatindex = computed(() => { 
  if (latestData.heatindex !== null) { 
    const temp = useFahrenheit.value ? (latestData.heatindex * 9/5 + 32) : latestData.heatindex;
    return `${temp.toFixed(2)} ${tempUnit.value}`; 
  } 
  return '--';
});

const pressure = computed(() => { 
  if (latestData.pressure !== null) { 
    return `${latestData.pressure.toFixed(2)} kPa`; 
  } 
  return '--';
});

const altitude = computed(() => { 
  if (latestData.altitude !== null) { 
    return `${latestData.altitude.toFixed(2)} m`; 
  } 
  return '--';
});

const moisture = computed(() => { 
  if (latestData.moisture !== null) { 
    return `${latestData.moisture.toFixed(2)} %`; 
  } 
  return '--';
});

// Watcher for payload updates
watch(payload, (data) => { 
  if (data) { 
    // Update latestData
    latestData.temperature = data.temperature;
    latestData.heatindex = data.heatindex;
    latestData.humidity = data.humidity;
    latestData.pressure = data.pressure;
    latestData.altitude = data.altitude;
    latestData.moisture = data.moisture;
    latestData.timestamp = data.timestamp;

    // Update charts
    if (points.value > 0) points.value--; 
    else shift.value = true; 
    
    const temp = useFahrenheit.value ? (data.temperature * 9/5) + 32 : data.temperature;
    const heat = useFahrenheit.value ? (data.heatindex * 9/5) + 32 : data.heatindex;
    
    tempHiChart.value?.series[0].addPoint({ y: parseFloat(temp.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value); 
    tempHiChart.value?.series[1].addPoint({ y: parseFloat(heat.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value); 
    humidHiChart.value?.series[0].addPoint({ y: parseFloat(data.humidity.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value);
    pressureHiChart.value?.series[0].addPoint({ y: parseFloat(data.pressure.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value);
    altitudeHiChart.value?.series[0].addPoint({ y: parseFloat(data.altitude.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value);
    moistureHiChart.value?.series[0].addPoint({ y: parseFloat(data.moisture.toFixed(2)), x: data.timestamp * 1000 }, true, shift.value);

    resetRefreshTimeout();
  }
});

onMounted(() => {
  CreateCharts(); 
  Mqtt.connect(); 
  setTimeout(() => { 
    Mqtt.subscribe("620165845");
  }, 3000);
});

onBeforeUnmount(() => {
  if (refreshTimeout) clearTimeout(refreshTimeout);
  Mqtt.unsubcribeAll();
});


const CreateCharts = async () => { 
    // TEMPERATURE CHART 
    
    tempHiChart.value = Highcharts.chart('container', { 
        chart: { zoomType: 'x', backgroundColor: '#1e1e1e'   }, 
        title: { text: 'Temperature Analysis (Live)', align: 'left', style: { color: '#FFFFFF' } }, 
       
        yAxis: { 
            title: { text: tempUnit.value, style:{color:'#FFFFFF'}}, 
            labels: { formatter: function() {
                    return useFahrenheit.value 
                        ? Highcharts.numberFormat(this.value * 9/5 + 32, 2) + ' °F'
                        : Highcharts.numberFormat(this.value, 2) + ' °C';
                }, style: { color: '#FFFFFF' } } ,
            gridLineColor: '#FFFFFF'
        }, 
        
        xAxis: { 
            type: 'datetime', 
            title: { text: 'Time', style:{color:'#FFFFFF'}},
            labels: { style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
         
        }, 
        
        tooltip: { shared:true, }, 
        legend: {
            itemStyle: { color: '#FFFFFF' } 
        },
        
        series: [ 
            { 
                name: 'Temperature', 
                type: 'spline', 
                data: [], 
                turboThreshold: 0, 
                color: Highcharts.getOptions().colors[0] 
            }, 
            
            { 
                name: 'Heat Index', 
                type: 'spline', 
                data: [], 
                turboThreshold: 0, 
                color: Highcharts.getOptions().colors[1] 
            } 
        ], 
    }); 

    // HUMIDITY CHART 
    
    humidHiChart.value = Highcharts.chart('container1', { 
        chart: { zoomType: 'x', backgroundColor: '#1e1e1e' }, 
        title: { text: 'Humidity Analysis (Live)', align: 'left', style: { color: '#FFFFFF' } }, 
        
        yAxis: { 
            title: { text: '%' , style:{color:'#FFFFFF'}}, 
            labels: { format: '{value} %', style:{color:'#FFFFFF'} },
            gridLineColor: '#FFFFFF' 
        }, 
        
        xAxis: { 
            type: 'datetime', 
            title: { text: 'Time', style:{color:'#FFFFFF'} }, 
            labels: { style: { color: '#FFFFFF' } },
             gridLineColor: '#FFFFFF'
        }, 
        
        tooltip: { shared:true, }, 
        legend: {itemStyle: { color: '#FFFFFF' } },
        
        series: [ 
            { 
                name: 'Humidity', 
                type: 'spline', 
                data: [], 
                turboThreshold: 0, 
                color: Highcharts.getOptions().colors[0] 
            }, 
            
           
        ], 
    }); 
    // pressure graph
    pressureHiChart.value = Highcharts.chart('container2', {
        chart: { zoomType: 'x', backgroundColor: '#1e1e1e' },
        title: { text: 'Pressure Analysis (Live)', align: 'left', style: { color: '#FFFFFF' } },
        yAxis: { 
            title: { text: 'kPa', style: { color: '#FFFFFF' } },
            labels: { format: '{value} kPa', style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        xAxis: { 
            type: 'datetime',
            title: { text: 'Time', style: { color: '#FFFFFF' } },
            labels: { style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        tooltip: { shared: true },
        legend: { itemStyle: { color: '#FFFFFF' } },
        series: [{
            name: 'Pressure',
            type: 'spline',
            data: [],
            turboThreshold: 0,
            color: '#4CAF50' // Green color for pressure
        }]
    });
     // Altitude Chart
     altitudeHiChart.value = Highcharts.chart('container3', {
        chart: { zoomType: 'x', backgroundColor: '#1e1e1e' },
        title: { text: 'Altitude Analysis (Live)', align: 'left', style: { color: '#FFFFFF' } },
        yAxis: { 
            title: { text: 'Meters', style: { color: '#FFFFFF' } },
            labels: { format: '{value} m', style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        xAxis: { 
            type: 'datetime',
            title: { text: 'Time', style: { color: '#FFFFFF' } },
            labels: { style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        tooltip: { shared: true },
        legend: { itemStyle: { color: '#FFFFFF' } },
        series: [{
            name: 'Altitude',
            type: 'spline',
            data: [],
            turboThreshold: 0,
            color: '#2196F3' // Blue color for altitude
        }]
    });

    // Moisture Chart
    moistureHiChart.value = Highcharts.chart('container4', {
        chart: { zoomType: 'x', backgroundColor: '#1e1e1e' },
        title: { text: 'Moisture Analysis (Live)', align: 'left', style: { color: '#FFFFFF' } },
        yAxis: { 
            title: { text: 'Value', style: { color: '#FFFFFF' } },
            labels: { format: '{value}', style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        xAxis: { 
            type: 'datetime',
            title: { text: 'Time', style: { color: '#FFFFFF' } },
            labels: { style: { color: '#FFFFFF' } },
            gridLineColor: '#FFFFFF'
        },
        tooltip: { shared: true },
        legend: { itemStyle: { color: '#FFFFFF' } },
        series: [{
            name: 'Moisture',
            type: 'spline',
            data: [],
            turboThreshold: 0,
            color: '#FF9800' // Orange color for moisture
        }]
    });








};


// WATCHERS 
watch(useFahrenheit, (newVal) => {
    if (tempHiChart.value) {
        tempHiChart.value.yAxis[0].update({
            title: { text: tempUnit.value }
        });
        tempHiChart.value.series.forEach(series => {
            series.update({
                data: series.data.map(point => {
                    return {
                        x: point.x,
                        y: newVal ? (point.y * 9/5) + 32 : (point.y - 32) * 5/9
                    };
                })
            });
        });
    }
});
watch(payload,(data)=> { 
    if(points.value > 0){ points.value -- ; } 
    else{ shift.value = true; } 
    const temp = useFahrenheit.value ? (data.temperature * 9/5) + 32 : data.temperature;
    const heat = useFahrenheit.value ? (data.heatindex * 9/5) + 32 : data.heatindex;
    
    tempHiChart.value.series[0].addPoint({y:parseFloat(temp.toFixed(2)) ,x: data.timestamp * 1000 }, true, shift.value); 
    tempHiChart.value.series[1].addPoint({y:parseFloat(heat.toFixed(2)) ,x: data.timestamp * 1000 }, true, shift.value); 
    humidHiChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)), x: data.timestamp * 1000}, true, shift.value);
    pressureHiChart.value?.series[0].addPoint({ y: parseFloat(data.pressure.toFixed(2)), x: data.timestamp * 1000}, true, shift.value);
    altitudeHiChart.value?.series[0].addPoint({ y: parseFloat(data.altitude.toFixed(2)), x: data.timestamp * 1000}, true, shift.value);
    moistureHiChart.value?.series[0].addPoint({ y: parseFloat(data.moisture.toFixed(2)), x: data.timestamp * 1000}, true, shift.value);
})



</script>


<style scoped>
/** CSS STYLE HERE */
Figure { 
border: 2px solid black; 
}

.circle-card {
    border-radius: 50% !important;
    aspect-ratio: 1/1 !important;
    display: flex !important;
    min-height: 180px; /* Adjust as needed */
    max-width: 580px !important;   /* Added to match height */
    width: 220px !important;       /* Fixed width */
    position: relative;
    overflow: hidden;
    margin: 0 auto;    
    position: relative;
    overflow: hidden;
}

.card-content {
    width: 100%;
    height: 100%;
    display: flex !important;
    flex-direction: column !important;
    align-items: center !important;
    justify-content: flex-start !important;
    padding-top: 12px !important; /* Space for subtitle */
}

.card-subtitle {
    margin-bottom: 15px !important;
    width: 100%;
    font-weight: bold;
    color: dimgrey;
    font-size: 1.0rem !important; 
    text-decoration: underline; /* Basic underline */
    text-decoration-thickness: 2px; /* Line thickness */
}

.card-value {
    display: flex !important;
    justify-content: center !important;
    align-items: center !important;
    flex-grow: 1;
    width: 100%;
}
.v-col-cards {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 8px;
}
.sep{
    margin-top: 20px;
    margin-bottom: 30px;
    background-color: #615555;
    border-radius: 25px;
    padding-left: 20px;
    padding-right: 10px;

}
.v-application__wrap{
    background-color: silver;
}

</style>
  