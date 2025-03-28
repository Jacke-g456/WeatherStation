<template>
    <v-container fluid class="con">
      <!-- First Row -->
      <v-row class="p-1" style="max-width: 1200px;">
        <v-col>
          <!-- Row 1, Column 1 -->

          <!--date picker-->
          <v-sheet class="p-2" height="250">
            <p>Enter date range for Analysis</p>
            <v-divider></v-divider>
  
            <v-text-field class="m-5" label="Start date" type="date" density="compact" variant="solo-inverted" flat style="max-width: 300px;" v-model="start" >
            
            </v-text-field>
  
            <v-text-field label="End date" type="date" density="compact" variant="solo-inverted" flat style="max-width: 300px;" v-model="end">
            
            </v-text-field>
  
            <v-spacer></v-spacer>
  
            <v-btn class="button-caption" text="Analyze"  variant="tonal" @click="updateLineCharts();updateHistogramCharts();updateScatterPlots();updateCards();">
            </v-btn>
          </v-sheet>





        </v-col>
      </v-row>
      
      <v-row class="row-con" style="max-width: 1200px;">
  
        <!--Temp card begin-->
        <v-col class="card-con" cols="12" sm="6" md="4" lg="2" >
          <v-card  width="200"  color="silver" density="compact" rounded="lg">
            <v-card-title class="text-center">Temperature</v-card-title>
            <v-card-text>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Min:</span>
                <v-chip size="small">{{ temperature.min }} °C</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Max:</span>
                <v-chip size="small">{{ temperature.max }} °C</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Range:</span>
                <v-chip size="small">{{ temperature.range }} °C</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Avg:</span>
                <v-chip size="small">{{ temperature.avg }} °C</v-chip>
              </div>
            </v-card-text>
          </v-card>
        </v-col>
         <!--Temp card end-->
  
        <!--Humid card begin-->
        <v-col class="card-con" cols="12" sm="6" md="4" lg="2" align="center">
          <v-card width="200"  color="silver" density="compact" rounded="lg">
            <v-card-title class="text-center">Humidity</v-card-title>
            <v-card-text>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Min:</span>
                <v-chip size="small">{{ humidity.min }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Max:</span>
                <v-chip size="small">{{ humidity.max }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Range:</span>
                <v-chip size="small">{{ humidity.range }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Avg:</span>
                <v-chip size="small" >{{ humidity.avg }} %</v-chip>
              </div>
            </v-card-text>
          </v-card>
        </v-col>

          <!--Humid card end-->

          <!--Pressure card start-->
          <v-col class="card-con" cols="12" sm="6" md="4" lg="2" align="center">
          <v-card width="200"  color="silver" density="compact" rounded="lg">
            <v-card-title class="text-center">Pressure</v-card-title>
            <v-card-text>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Min:</span>
                <v-chip size="small">{{ pressure.min }} kPa</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Max:</span>
                <v-chip size="small">{{ pressure.max }} kPa</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Range:</span>
                <v-chip size="small">{{ pressure.range }} kPa</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Avg:</span>
                <v-chip size="small">{{ pressure.avg }} kPa</v-chip>
              </div>
            </v-card-text>
          </v-card>
        </v-col>
          <!--Pressure card end-->

          <!--Altitude card start-->
          <v-col class="card-con" cols="12" sm="6" md="4" lg="2" align="center">
          <v-card width="200"  color="silver" density="compact" rounded="lg">
            <v-card-title class="text-center">Altitude</v-card-title>
            <v-card-text>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Min:</span>
                <v-chip size="small">{{ altitude.min }} m</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Max:</span>
                <v-chip size="small">{{ altitude.max }} m</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Range:</span>
                <v-chip size="small">{{ altitude.range }} m</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Avg:</span>
                <v-chip size="small">{{ altitude.avg }} m</v-chip>
              </div>
            </v-card-text>
          </v-card>
        </v-col>
          <!--Altitude card end-->

          <!--moisture card start-->
          <v-col class="card-con" cols="12" sm="6" md="4" lg="2" align="center">
          <v-card width="200" color="silver" density="compact" rounded="lg">
            <v-card-title class="text-center">Moisture</v-card-title>
            <v-card-text>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Min:</span>
                <v-chip size="small">{{ moisture.min }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Max:</span>
                <v-chip size="small">{{ moisture.max }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Range:</span>
                <v-chip size="small">{{ moisture.range }} %</v-chip>
              </div>
              <div class="d-flex align-center mb-2">
                <span class="text-caption mr-2">Avg:</span>
                <v-chip size="small">{{ moisture.avg }} %</v-chip>
              </div>
            </v-card-text>
          </v-card>
        </v-col>
          <!--moisture card end-->
         </v-row>
         </v-container>

         <v-container fluid class="con">
        
        
      
        <v-row style="max-width: 1200px;">
        <!-- Row 2 -->

        <v-col cols="12">
        <!-- Row 2, Column 1 -->
          
          <figure class="highcharts-figure">
            <div id="container"></div>
          </figure>

        </v-col>
        </v-row>
        </v-container>
        <v-container fluid class="con">
          <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 2, Column 2 -->

          <figure class="highcharts-figure">
            <div id="container0"></div>
          </figure>

        </v-col>
      </v-row>
      </v-container>
      <v-container fluid class="con">
          <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 2, Column 2 -->

          <figure class="highcharts-figure">
            <div id="contain1"></div>
          </figure>

        </v-col>
      </v-row>
      </v-container>
      <v-container fluid class="con">
  
      
      <v-row style="max-width: 1200px;">
      <!-- Row 3 -->

        <v-col class="border" cols="12">
        <!-- Row 3, Column 1 -->
          <figure class="highcharts-figure">
            <div id="container1"></div>
          </figure>

        </v-col>
        </v-row>
      </v-container>

      <v-container fluid class="con">
        <v-row style="max-width: 1200px;">
        <v-col cols="12">
        <!-- Row 3, Column 2 -->

          <figure class="highcharts-figure">
            <div id="container2"></div>
          </figure>

        </v-col>
        </v-row>
      </v-container>

      <v-container fluid class="con">
        <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 3, Column 3 -->

          <figure class="highcharts-figure">
            <div id="container3"></div>
          </figure>

        </v-col>


      </v-row>
    </v-container>
    <v-container fluid class="con">
        <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 3, Column 3 -->

          <figure class="highcharts-figure">
            <div id="container4"></div>
          </figure>

        </v-col>


      </v-row>
    </v-container>


    <v-container fluid class="con">
        <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 3, Column 3 -->

          <figure class="highcharts-figure">
            <div id="container5"></div>
          </figure>

        </v-col>


      </v-row>
    </v-container>

    <v-container fluid class="con">
        <v-row style="max-width: 1200px;">

        <v-col cols="12">
        <!-- Row 3, Column 3 -->

          <figure class="highcharts-figure">
            <div id="container6"></div>
          </figure>

        </v-col>


      </v-row>
    </v-container>
</template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";
import { useMqttStore } from '@/store/mqttStore'; 
import { useAppStore } from "@/store/appStore";
import { storeToRefs } from "pinia";

// Highcharts, Load the exporting module and Initialize exporting module.
import Highcharts from 'highcharts';
import more from 'highcharts/highcharts-more';
import Exporting from 'highcharts/modules/exporting';
 
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();
const Mqtt = useMqttStore();
const AppStore = useAppStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
const tempHiChart = ref(null); 
const humidChart = ref(null); 
const pressureHiChart = ref(null);
const altitudeHiChart = ref(null);
const moistureHiChart = ref(null);
const histogramChart = ref(null);
const scatterPlot1 = ref(null); 
const scatterPlot2 = ref(null); 
const scatterPlot3 = ref(null); 
const scatterPlot4 = ref(null); 
const scatterPlot5 = ref(null); 
const points = ref(10); // Specify the quantity of points to be shown on the live graph simultaneously.
const shift = ref(false); // Delete a point from the left side and append a new point to the right side of the graph.
const start   = ref("");
const end    = ref("");
const temperature = reactive({"min":0,"max":0,"avg":0,"range":0});
const humidity = reactive({"min":0,"max":0,"avg":0,"range":0});
const altitude = reactive({"min":0,"max":0,"avg":0,"range":0});
const pressure = reactive({"min":0,"max":0,"avg":0,"range":0});
const moisture = reactive({"min":0,"max":0,"avg":0,"range":0});



// Add reload timer variable
let reloadTimer = null;

onMounted(() => {
    CreateCharts();
    Mqtt.connect();
    
    // Set up auto-reload
    //reloadTimer = setTimeout(() => {
    //    window.location.reload(true); // true forces a hard reload from server
    //}, 120000); // 20 seconds
});

onBeforeUnmount(() => {
    // Cleanup timer if component unmounts before reload
    //if (reloadTimer) {
        clearTimeout(reloadTimer);
   // }
    Mqtt.unsubcribeAll();
});

const CreateCharts = async () => {

    // TEMPERATURE CHART
    tempHiChart.value = Highcharts.chart('container', {
        chart: { zoomType: 'x' },
        title: { text: 'Air Temperature and Heat Index Analysis', align: 'left' },
        subtitle: { text: 'The heat index, also known as the "apparent temperature," is a measure that combines air temperature and relative humidity to assess how hot it feels to the human body. The relationship between heat index and air temperature is influenced by humidity levels. As humidity increases, the heat index also rises, making the perceived temperature higher than the actual air temperature.' },
        yAxis: {
            title: { text: 'Air Temperature & Heat Index' , style:{color:'#000000'}},
            labels: { format: '{value} °C' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, 
            pointFormat: 'Humidity: {point.x} % <br/> Temperature: {point.y} °C'
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

    humidChart.value = Highcharts.chart('container0', {
        chart: { zoomType: 'x' },
        title: { text: 'Humidity Analysis', align: 'left' },
        subtitle: { text: 'This chart shows the humidity levels over time, which impacts the perceived temperature.' },
        yAxis: {
            title: { text: 'Humidity', style: { color: '#000000' } },
            labels: { format: '{value} %' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style: { color: '#000000' } },
        },
        tooltip: {
            shared: true,
            pointFormat: 'Humidity: {point.x} % <br/> Temperature: {point.y} °C'
        },
        series: [
            {
                name: 'Humidity',
                type: 'spline',
                data: [], // Replace with actual dynamic data
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            }
        ],
    });
   pressureHiChart.value = Highcharts.chart('contain1', {
        chart: { zoomType: 'x' },
        title: { text: 'Pressure Analysis', align: 'left' },
        subtitle: { text: 'This chart shows the pressure levels over time.' },
        yAxis: {
            title: { text: 'Pressure', style: { color: '#000000' } },
            labels: { format: '{value} kPa' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style: { color: '#000000' } },
        },
        tooltip: {
            shared: true,
            pointFormat: 'Pressure: {point.x} kPa'
        },
        series: [
            {
                name: 'Pressure',
                type: 'spline',
                data: [], // Replace with actual dynamic data
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            }
        ],
    });
   

    histogramChart.value = Highcharts.chart('container1', {
        chart: { zoomType: 'x' },
        title: { text: 'Frequency Distribution Analysis', align: 'left' },
        subtitle: {
          text: 'This chart shows the frequency distribution of Temperature, Humidity, and Heat Index.'
        },
        xAxis: {
          title: { text: 'Temperature Ranges (°C)' }
        },
        yAxis: {
          title: { text: 'Frequency', style: { color: '#000000' } },
          labels: { format: '{value}' }
        },
        tooltip: {
          shared: true,
          pointFormat: 'Humidity: {point.x} % <br/> Temperature: {point.y} °C'
        },
        series: [
          {
            name: 'Temperature',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[0]
          },
          {
            name: 'Humidity',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[1]
          },
          {
            name: 'Heat Index',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[2]
          },
          {
            name: 'Pressure',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[3]
          },
          {
            name: 'Altitude',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[4]
          },
          {
            name: 'Moisture',
            type: 'column',
            data: [], // Replace with actual data
            color: Highcharts.getOptions().colors[5]
          }
        ],
    });

    scatterPlot1.value = Highcharts.chart('container2', {
        chart: { type: 'scatter', zoomType: 'x' },
        title: { text: 'Temperature & Heat Index Correlation Analysis', align: 'left' },
        subtitle: {
          text: 'Visualize the relationship between Temperature and Heat Index as well as revealing patterns or trends in the data.'
        },
        xAxis: {
          title: { text: 'Temperature' },
          labels: { format: '{value} °C' },
          startOnTick: true,
          endOnTick: true,
          showLastLabel: true
        },
        yAxis: {
          title: { text: 'Heat Index' },
          labels: { format: '{value} °C' },
        },
        tooltip: {
          pointFormat: 'Temperature: {point.x} °C <br/> Heat Index: {point.y} °C'
        },
        plotOptions: {
            scatter: {
                marker: {
                    radius: 2.5,
                    symbol: 'circle',
                    states: {
                        hover: {
                            enabled: true,
                            lineColor: 'rgb(100,100,100)'
                        }
                    }
                },
                states: {
                    hover: {
                        marker: {
                            enabled: false
                        }
                    }
                },
                jitter: {
                    x: 0.005
                }
            }
        },
        series: [{
          name: 'Analysis',
          id: 'analysis',
          data: [], // Use Humidity as x and Heat Index as y
          marker: { symbol:'circle', radius: 5 }
        }],
    });

    scatterPlot2.value = Highcharts.chart('container3', {
        chart: { type: 'scatter', zoomType: 'x' },
        title: { text: 'Humidity & Heat Index Correlation Analysis', align: 'left' },
        subtitle: {
          text: 'Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data.'
        },
        xAxis: {
          title: { text: 'Humidity' },
          labels: { format: '{value} %' },
          startOnTick: true,
          endOnTick: true,
          showLastLabel: true
        },
        yAxis: {
          title: { text: 'Heat Index' },
          labels: { format: '{value} °C' },
        },
        tooltip: {pointFormat: 'Humidity: {point.x} % <br/> Heat Index: {point.y} °C'},
        plotOptions: {
            scatter: {
                  marker: {
                          radius: 2.5,
                          symbol: 'circle',
                           states: {hover: {enabled: true, lineColor: 'rgb(100,100,100)' }}},
                           states: { hover: {marker: {enabled: false }}},
                           jitter: { x: 0.005}
                           }
                    },


        series: [{
          name: 'Analysis',
          id: 'analysis',
          data: [], // x is Humidity, y is Heat Index 
          marker: { symbol:'circle', radius: 5 }
        }],
    });
    scatterPlot3.value = Highcharts.chart('container4', {
        chart: { type: 'scatter', zoomType: 'x' },
        title: { text: 'Temperature & Air Pressure Correlation Analysis', align: 'left' },
        subtitle: {
          text: 'Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data.'
        },
        xAxis: {
          title: { text: 'Temperature' },
          labels: { format: '{value} °C' },
          startOnTick: true,
          endOnTick: true,
          showLastLabel: true
        },
        yAxis: {
          title: { text: 'Air Pressure' },
          labels: { format: '{value} kPa' },
        },
        tooltip: {pointFormat: 'Temperature: {point.x} °C <br/> Pressure: {point.y} kPa'},
        plotOptions: {
            scatter: {
                  marker: {
                          radius: 2.5,
                          symbol: 'circle',
                           states: {hover: {enabled: true, lineColor: 'rgb(100,100,100)' }}},
                           states: { hover: {marker: {enabled: false }}},
                           jitter: { x: 0.005}
                           }
                    },


        series: [{
          name: 'Analysis',
          id: 'analysis',
          data: [], // x is Humidity, y is Heat Index 
          marker: { symbol:'circle', radius: 5 }
        }],
    });
    scatterPlot4.value = Highcharts.chart('container5', {
        chart: { type: 'scatter', zoomType: 'x' },
        title: { text: 'Temperature & Soil Moisture Correlation Analysis', align: 'left' },
        subtitle: {
          text: 'Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data.'
        },
        xAxis: {
          title: { text: 'Temperature' },
          labels: { format: '{value} °C' },
          startOnTick: true,
          endOnTick: true,
          showLastLabel: true
        },
        yAxis: {
          title: { text: 'Soil Moisture' },
          labels: { format: '{value} %' },
        },
        tooltip: {pointFormat: 'Temperature: {point.x} °C <br/> Soil Moisture: {point.y} %'},
        plotOptions: {
            scatter: {
                  marker: {
                          radius: 2.5,
                          symbol: 'circle',
                           states: {hover: {enabled: true, lineColor: 'rgb(100,100,100)' }}},
                           states: { hover: {marker: {enabled: false }}},
                           jitter: { x: 0.005}
                           }
                    },


        series: [{
          name: 'Analysis',
          id: 'analysis',
          data: [], // x is Humidity, y is Heat Index 
          marker: { symbol:'circle', radius: 5 }
        }],
    });
    scatterPlot5.value = Highcharts.chart('container6', {
        chart: { type: 'scatter', zoomType: 'x' },
        title: { text: 'Altitude & Air Pressure Correlation Analysis', align: 'left' },
        subtitle: {
          text: 'Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data.'
        },
        xAxis: {
          title: { text: 'Al;titude' },
          labels: { format: '{value} m' },
          startOnTick: true,
          endOnTick: true,
          showLastLabel: true
        },
        yAxis: {
          title: { text: 'Air Pressure' },
          labels: { format: '{value} kPa' },
        },
        tooltip: {pointFormat: 'Altitude: {point.x} m <br/> Air Pressure: {point.y} kPa'},
        plotOptions: {
            scatter: {
                  marker: {
                          radius: 2.5,
                          symbol: 'circle',
                           states: {hover: {enabled: true, lineColor: 'rgb(100,100,100)' }}},
                           states: { hover: {marker: {enabled: false }}},
                           jitter: { x: 0.005}
                           }
                    },


        series: [{
          name: 'Analysis',
          id: 'analysis',
          data: [], // x is Humidity, y is Heat Index 
          marker: { symbol:'circle', radius: 5 }
        }],
    });
};

const updateLineCharts = async ()=>{
    if(!!start.value && !!end.value){
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const data = await AppStore.getAllInRange(startDate,endDate);
        console.log(data)
        // Create arrays for each plot
        let temperature = [];
        let heatindex = [];
        let humidity = [];
        let pressure =[];
        // Iterate through data variable and transform object to format recognized by highcharts
        data.forEach(row => {
            temperature.push({"x": row.timestamp * 1000, "y": parseFloat(row.temperature.toFixed(2)) });
            heatindex.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
            humidity.push({ "x": row.timestamp * 1000,"y": parseFloat(row.humidity.toFixed(2)) });
            pressure.push({ "x": row.timestamp * 1000,"y": parseFloat(row.pressure.toFixed(2)) });
        });
        // Add data to Temperature and Heat Index chart
        tempHiChart.value.series[0].setData(temperature);
        tempHiChart.value.series[1].setData(heatindex);
        humidChart.value.series[0].setData(humidity);
        pressureHiChart.value.series[0].setData(pressure);
    }
}

const updateHistogramCharts = async ()=>{
    if(!!start.value && !!end.value){
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const temp = await AppStore.getFreqDistro("temperature",startDate,endDate);
        const humid = await AppStore.getFreqDistro("humidity",startDate,endDate);
        const hi = await AppStore.getFreqDistro("heatindex",startDate,endDate);
        const pre = await AppStore.getFreqDistro("pressure",startDate,endDate);
        const alt = await AppStore.getFreqDistro("altitude",startDate,endDate);
        const moist = await AppStore.getFreqDistro("moisture",startDate,endDate);
        // Create arrays for each plot
        let temperature = [];
        let heatindex = [];
        let humidity = [];
        let pressure =[];
        let altitude = [];
        let moisture = [];

        temp.forEach(row => {
            temperature.push({"x": row["_id"],"y": row["count"]})
        });
        humid.forEach(row => {
            humidity.push({"x": row["_id"],"y": row["count"]})
        });
        hi.forEach(row => {
            heatindex.push({"x": row["_id"],"y": row["count"]})
        });
        pre.forEach(row => {
            pressure.push({"x": row["_id"],"y": row["count"]})
        });
        alt.forEach(row => {
            altitude.push({"x": row["_id"],"y": row["count"]})
        });
        moist.forEach(row => {
            moisture.push({"x": row["_id"],"y": row["count"]})
        });
        // Add data to Temperature and Heat Index chart
        histogramChart.value.series[0].setData(temperature);
        histogramChart.value.series[1].setData(heatindex);
        histogramChart.value.series[2].setData(humidity);
        histogramChart.value.series[3].setData(pressure);
        histogramChart.value.series[4].setData(altitude);
        histogramChart.value.series[5].setData(moisture);
        
    }
}

const updateScatterPlots = async ()=>{
    if(!!start.value && !!end.value){
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const data = await AppStore.getAllInRange(startDate,endDate);
        
        
        // Create arrays for each plot
        let graph1 = [];
        let graph2 = [];
        let graph3=[];
        let graph4=[];
        let graph5=[];

        data.forEach(row => {
            graph1.push([parseFloat(row.temperature.toFixed(2)),parseFloat(row.heatindex.toFixed(2))])
            graph2.push([parseFloat(row.humidity.toFixed(2)),parseFloat(row.heatindex.toFixed(2))])
            graph3.push([parseFloat(row.temperature.toFixed(2)),parseFloat(row.pressure.toFixed(2))])
            graph4.push([parseFloat(row.temperature.toFixed(2)),parseFloat(row.moisture.toFixed(2))])
            graph5.push([parseFloat(row.altitude.toFixed(2)),parseFloat(row.pressure.toFixed(2))])
        });
        
        // Add data to Temperature and Heat Index chart
        scatterPlot1.value.series[0].setData(graph1);
        scatterPlot2.value.series[0].setData(graph2);
        scatterPlot3.value.series[0].setData(graph3);
        scatterPlot4.value.series[0].setData(graph4);
        scatterPlot5.value.series[0].setData(graph5);
    }
    }
  
    


const updateCards = async () => {
    // Retrieve Min, Max, Avg, Spread/Range
    if(!!start.value && !!end.value){
        // 1. Convert start and end dates collected fron TextFields to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;

        // 2. Fetch data from backend by calling the API functions
        const temp = await AppStore.getTemperatureMMAR(startDate,endDate);
        const humid = await AppStore.getHumidityMMAR(startDate,endDate);
        const alt = await AppStore.getAltitudeMMAR(startDate,endDate);
        const pres = await AppStore.getPressureMMAR(startDate,endDate);
        const moist = await AppStore.getMoistureMMAR(startDate,endDate);

        console.log(temp);
        console.log(humid);
        console.log(pres);
        console.log(alt);
        console.log(moist);
        temperature.max = temp[0].max.toFixed(1);

        //3. complete for min, avg and range
        temperature.avg = temp[0].avg.toFixed(1);
        temperature.range = temp[0].range.toFixed(1);
        humidity.min = humid[0].min.toFixed(1);
        humidity.avg = humid[0].avg.toFixed(1);
        humidity.range = humid[0].range.toFixed(1);

        //4. complete max, min, avg and range for the humidity variable
        humidity.max = humid[0].max.toFixed(1);
        temperature.min = temp[0].min.toFixed(1);
        altitude.max = alt[0].max.toFixed(1);
        altitude.avg = alt[0].avg.toFixed(1);
        altitude.min = alt[0].min.toFixed(1);
        altitude.range = alt[0].range.toFixed(1);
        pressure.avg = pres[0].avg.toFixed(1);
        pressure.max = pres[0].max.toFixed(1);
        pressure.min = pres[0].min.toFixed(1);
        pressure.range = pres[0].range.toFixed(1);
        moisture.max = moist[0].max.toFixed(1);
        moisture.range = moist[0].range.toFixed(1);
        moisture.avg = moist[0].avg.toFixed(1);
        moisture.min = moist[0].min.toFixed(1);

    }
}





</script>


<style scoped>
/** CSS STYLE HERE */
.con{
  background-color: #615555;
  margin-top: 20px;
  border-radius: 20px;
  padding-right: 100px;
}
.v-sheet{
  padding-left: 20px;
  margin-left: 400px;
  margin-right: 400px;
  padding-top: 20px;
  border-radius:20px;
  background-color: silver;
}
.text-caption{
  margin-left: 10px;
}
.button-caption{
  margin-left: 100px;
}
.v-card-text {
  padding-left: 16px !important;
  padding-right: 16px !important;
}
.card-con{
  margin-right:30px;
}
.row-con{
  padding-left:50px ;
}

.v-application__wrap{
  background-color: silver;
}

</style>