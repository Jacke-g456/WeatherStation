  <template>
         <VToolbar flat density="compact" class="nav" height="150" >
            <img height="100" width="120" class="mt-2" src="@/assets/UWI logo .png" />
            <h1 class="ml-6 head">UWI Weather Station</h1>
            <VContainer fluid>
                    <VRow align="center" justify="center">
                        <VCol cols="1" align="left" >
                             
                        </VCol>

                        <VCol cols="6"  align="center"   > 

                            <RouterLink class="route" :to="{ name: 'Home' }" >
                                <VBtn class="custom-btn-text"   density="compact"  color="#C0C0C0" :variant="(route.name == 'Home')? 'tonal':'text'">Home</VBtn>
                            </RouterLink>
                            <RouterLink class="route" :to="{ name: 'About US' }" >
                                <VBtn class="custom-btn-text"   density="compact"  color="#C0C0C0" :variant="(route.name == 'About US')? 'tonal':'text'">About US</VBtn>
                            </RouterLink>
                            <RouterLink class="route" :to="{ name: 'Live' }" >
                                <VBtn class="custom-btn-text"   density="compact"  color="#C0C0C0" :variant="(route.name == 'Live')? 'tonal':'text'">Live</VBtn>
                            </RouterLink>
                            <RouterLink class="route" :to="{ name: 'Analysis' }" >
                                <VBtn class="custom-btn-text"   density="compact"  color="#C0C0C0" :variant="(route.name == 'Analysis')? 'tonal':'text'">Analysis</VBtn>
                            </RouterLink>
                        

                            <!-- Add Links Below -->
                                                                         

                        </VCol>
                        <VCol cols="1" align="right">
                        <!--    <VBtn size="x-small" :elevation="0"  icon @click="darkmode = !darkmode">                  
                                <VIcon v-if="darkmode" icon="mdi:mdi-weather-night"   ></VIcon>
                                <VIcon v-else  icon="mdi:mdi-white-balance-sunny"  ></VIcon>
                            </VBtn> -->
                        </VCol>
                    </VRow>
                </VContainer>
            </VToolbar>
  </template>

  
  <script setup>
    import { useRoute,useRouter } from "vue-router";
    import { useTheme } from 'vuetify';  
    import { ref ,watch ,onMounted ,onBeforeMount } from 'vue';


  
    // VARIABLES 
    const theme       = useTheme();
    const darkmode    = ref(false); 
    const router      = useRouter();  
    const route       = useRoute();  

    // WATCHERS
    watch(darkmode,  (mode) => {
    theme.global.name.value = mode ?  'darkMode' : 'lightMode';
    localStorage.setItem("theme",mode ? 'darkMode' : 'lightMode');  
    });


    // FUNCTIONS
    onMounted(()=>{
 

    });

    onBeforeMount(()=>{
        // SAVE THEME TO LOCALSTORAGE MAKING IT PERSIST BROWSER REFRESH

        if(localStorage.getItem("theme") != null){
            theme.global.name.value = localStorage.getItem("theme");
            darkmode.value = theme.global.current.value.dark;
        }
        else{
            localStorage.setItem("theme",theme.global.current.value.dark ? 'darkMode' : 'lightMode');
            darkmode.value = theme.global.current.value.dark;    
        }  
    });

 
  </script>

  <style>
    .route {
        
        margin-left: 8px;
        margin-right: 8px; 
    }
    .nav{
        background-color: #615555 !important;
    }
    .head{
        color:silver;
    }
    .custom-btn-text{
        font-size: 18px; /* Adjust as needed */
        font-weight: 500;
    }
  </style>
  