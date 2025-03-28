<template>
  
  <VContainer class="fill-height ">
    <VResponsive class="align-center text-center fill-height">
      <img height="350" width="600" class="mb-5" src="@/assets/physics.jpg" />

      <div class="text-body-2 font-weight-light mb-n1">Welcome to the</div>

      <h1 class="text-h2 font-weight-bold">UWI Weather Station</h1>
      <div class="text-body-1 font-weight-light mt-1">of the the Mona Campus' Physics Department</div>
 

      <div class="py-14" />

      <VRow class="d-flex align-center justify-center">
        <VCol cols="auto">
          <VBtn
            href="https://www.mona.uwi.edu//"
            min-width="164"
            rel="noopener noreferrer"
            target="_blank"
            variant="text"
          >
            <VIcon icon="mdi-view-dashboard" size="large" start />

            Campus
          </VBtn>
        </VCol>

        <VCol cols="auto">
          <VBtn
            color="cyan"
            href="https://www.mona.uwi.edu/physics/home"
            min-width="228"
            rel="noopener noreferrer"
            size="x-large"
            target="_blank"
            variant="flat"
          >
            <VIcon icon="mdi-speedometer" size="large" start />

            Department
          </VBtn>
        </VCol>

        <VCol cols="auto">
          <VBtn
            href="https://support.mona.uwi.edu/visitor/index.php?/Default/LiveChat/Chat/Request/_sessionID=/_promptType=chat/_proactive=0/_filterDepartmentID=5/_randomNumber=1ha9ddgs9kaijf1s75tbzgmvjyv2ri7x/_fullName=/_email=/"
            min-width="164"
            rel="noopener noreferrer"
            target="_blank"
            variant="text"
          >
            <VIcon icon="mdi-account-group" size="large" start />

            Community
          </VBtn>
        </VCol>
      </VRow>
    </VResponsive>
  </VContainer>

</template>

<script setup>
  import { storeToRefs } from 'pinia';
  import { useMqttStore } from '@/store/mqttStore';
  import { ref,reactive, watch, onMounted, onBeforeUnmount } from 'vue';


// VARIABLES


// FUNCTIONS
onMounted(()=>{
   
});

onBeforeUnmount(()=>{ 
  
});
</script>
