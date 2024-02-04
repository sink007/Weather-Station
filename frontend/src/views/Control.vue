<template>
     <v-container class="container" fluid>
        <v-row class="row" max-width="1200px" justify="center">
            <v-col class="col col1" align="center"> 
                <v-sheet class="sheet sheet1 rounded-t-lg mb-1">
                    <VCard class="text-secondary" 
                        title= "LED Controls" 
                        subtitle="Recent Settings" 
                        variant="tonal" 
                        flat color="surface">
                    </VCard>         
                </v-sheet>
                <v-sheet class="sheet sheet2">
                    <VCard class="pt-5" variant="tonal" color="surface">
                        <v-slider 
                            v-model="led.brightness"
                            class="pt-2 bg-surface"
                            append-icon="mdi:mdi-car-light-high"
                            density="compact"
                            thumb-size="16"
                            color="secondary"
                            label="Brightness"
                            direction="horizontal"
                            min="0"
                            max="250"
                            step="10"
                            show-ticks
                            thumb-label="always"> </v-slider>
                    </VCard>
                </v-sheet>
                <v-sheet class="sheet sheet3 mb-1" justify="center" align="center">
                    <VCard class="pt-5" variant="tonal" color="surface">
                        <v-slider 
                            v-model="led.nodes"
                            class="pt-2 bg-surface"
                            append-icon="mdi:mdi-led-on"
                            density="compact"
                            thumb-size="16"
                            color="secondary"
                            label="LED Nodes"
                            direction="horizontal"
                            min="1"
                            max="7"
                            step="1"
                            show-ticks
                            thumb-label="always"> </v-slider>
                    </VCard>
                </v-sheet> 
                <v-sheet class="sheet sheet4 mb-1 pa-2" justify="center" align="center">
                    <v-progress-circular rotate="0" size="200" width="15" :model-value="led.nodes *15" :color="indicatorColor">
                        <span class="text-onSurface font-weight-bold">{{ led.nodes }} LED(s)</span>
                    </v-progress-circular>
                </v-sheet> 
            </v-col>
            <v-col class="col col2" align="center"> 
                <v-color-picker v-model="led.color">

                </v-color-picker>
            </v-col>
    

        </v-row>

     </v-container>
</template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";
import { useMqttStore } from '@/store/mqttStore'; // Import Mqtt Store
import { storeToRefs } from "pinia";
    
const Mqtt = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();  
const led = reactive({"brightness":255,"nodes":1,"color":{ r: 255, g: 0, b: 255, a: 1 }});
let timer, ID = 1000;

// FUNCTIONS
onMounted(()=>{
        // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
        Mqtt.connect(); // Connect to Broker located on the backend
        setTimeout( ()=>{
        // Subscribe to each topic
        Mqtt.subscribe("620155784");
        Mqtt.subscribe("620155784_pub");
        Mqtt.subscribe("620155784_sub");
        },3000);
});


onBeforeUnmount(()=>{
        // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
        // unsubscribe from all topics
        Mqtt.unsubcribeAll();
});

watch(led,(controls)=>{
    clearTimeout(ID);
    ID = setTimeout(()=>{
        const message =
        JSON.stringify({"type":"controls","brightness":controls.brightness,"leds":controls.nodes,"color": controls.color});
        Mqtt.publish("620155784_sub",message); // Publish to a topic subscribed to by the hardware
    },1000)
})

const indicatorColor = computed(()=>{
    return `rgba(${led.color.r},${led.color.g},${led.color.b},${led.color.a})`
})

</script>


<style scoped>
/** CSS STYLE HERE */
.sheet{
    color: surface;
    elevation:0;
    max-width: 800px;
    width: 100%;
}


</style>
  