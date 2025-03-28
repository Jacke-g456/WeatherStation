<template>
    <div id = "sep" class="Aim">
        <h1>Aim</h1>
        <p>The UWI Weather Station was established to monitor key weather parameters such as air temperature, heat index, humidity, air pressure, soil moisture, and altitude. Its primary objective is to provide valuable data for research on climate trends, environmental changes, and agricultural planning. The collected data will contribute to scientific studies and, in 
            the long run, support the development of climate policies aimed at mitigating the effects of global warming.</p>

            <img height="500" width="720" class="mt-2 weather" src="@/assets/weather.jpg" />
    </div>

    <div id = "sep" class="Brief History">
        <h1>Brief History</h1>
        <p>Founded in January 2025 by research students and professors from the Physics Department, the UWI Weather Station emerged as an academic initiative to enhance climate research. The project was driven by the need for localized, high-quality weather data that could help researchers understand regional climate patterns. Over time, the station aims to 
            expand its capabilities, integrating advanced sensors and data analysis tools to improve accuracy and impact.</p>

    </div>

    <div id = "sep" class="Devices used">
        <h1>Devices used</h1>
        <p>
            The weather station utilizes a range of sensors to capture environmental data. The DHT22 sensor measures temperature and humidity, providing essential insights into atmospheric conditions. The BMP280 sensor records air pressure and altitude, aiding in weather pattern analysis. Additionally, a capacitive soil moisture sensor monitors soil conditions, which is crucial for agricultural and ecological studies. These instruments 
            work together to offer a comprehensive view of the local climate, enabling researchers to track and analyze changes over time.
        </p>

        <img height="200" width="300" class="mt-2 device" src="@/assets/dht.jpg" />
        <img height="200" width="300" class="mt-2 device" src="@/assets/bmp.jpg" />
        <img height="200" width="300" class="mt-2 device" src="@/assets/soil.jpg" />
    </div>

    <div id = "sep" class="Links">
        <h1>Links</h1>
        <h2>If you are interested in the learning more about the devices used the links to their 
            datasheets are below:
        </h2>

        <VBtn
            href="https://cdn.sparkfun.com/assets/f/7/d/9/c/DHT22.pdf"
            min-width="164"
            rel="noopener noreferrer"
            target="_blank"
            variant="text"
          >
            <VIcon icon="mdi-view-dashboard" size="large" start />

            DHT22
          </VBtn>
       
        <VBtn
            href="https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp280/"
            min-width="164"
            rel="noopener noreferrer"
            target="_blank"
            variant="text"
          >
            <VIcon icon="mdi-view-dashboard" size="large" start />

            BMP280
          </VBtn>
          <VBtn
            href="https://www.datocms-assets.com/28969/1662716326-hw-101-hw-moisture-sensor-v1-0.pdf"
            min-width="164"
            rel="noopener noreferrer"
            target="_blank"
            variant="text"
          >
            <VIcon icon="mdi-view-dashboard" size="large" start />

            Capacitive Soil Sensor
          </VBtn>
        
    </div>
</template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";
import {useMqttStore} from "@/store/mqttStore";
import {storeToRefs } from "pinia";
import { VContainer, VRow, VCol, VCard, VSlider, VProgressCircular, VColorPicker } from 'vuetify/components';
 
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();  
const led = reactive({"brightness": 255, "leds": 1, "color": {r: 255, g: 0, b: 255, a: 1}});
const Mqtt = useMqttStore();
const {payload, payloadTopic } = storeToRefs(Mqtt);
let timer, ID = 1000; // Unique ID for this component

// FUNCTIONS
onMounted(()=>{
    // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
    Mqtt.connect();
    setTimeout( ()=>{ Mqtt.subscribe("620165845")}, 3000);
});


onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});

// WATCHERS
watch(led,(controls)=>{
    clearTimeout(ID);
    ID = setTimeout(()=>{
        const message = JSON.stringify({"type":"controls","brightness":controls.brightness,"leds":controls.leds,"color":
        controls.color});
        Mqtt.publish("620165845_sub",message); // Publish to a topic subscribed to by the hardware
    },1000)
})



</script>


<style scoped>
/** CSS STYLE HERE */
#sep {
    color: #615555;
    margin-top: 20px;
    margin-bottom: 100px;
    border-radius: 10px;
    padding-left: 20px;
    padding-right: 30px;
    background-color: #e0d2c0;
}
.weather{
    margin-left: 300px;
    margin-bottom: 30px;
}
h1{
    text-align: center;
}
.device{
    margin-left: 60px;
    margin-bottom: 40px;
    margin-top:30px;
}
p{
    margin-bottom: 30px;
}
vBtn{
    size:20px
}

</style>
  