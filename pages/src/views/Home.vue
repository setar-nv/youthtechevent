<template>
  <div class="home">
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->
    <div class="container">
      <!-- Main component for a primary marketing message or call to action -->
      <div class="well">
        <div class="row">
          <h2>ESP8266 Built-in OLED – Heltec WiFi Kit 8</h2>
          <p class="small">May 4, 2019</p>
          <div class="text-left col-sm-8">
            <h4>A  set-up guide for the Heltec WiFi Kit 8 development board (an ESP8266 with built-in OLED display).</h4>
            <p>Follow the easy steps below to get up and running with this board using standard Arduino libraries.</p>

            <p>This board is based on the ESP8266 chip and has onboard WiFi,  a 0.96inch 128*32 OLED display, lithium battery 
              connector charging and a CP2014 USB to serial interface. It also works with the Arduino IDE!</p>
          </div>

          <img class="col-sm-4 modal-image" v-bind:src="imageBadge" @click="showImage(imageBadge, imageBadgeTitle)">

        </div>
      </div>

      <div class="well">
        <h3>Setting Up the Arduino IDE for the ESP8266 Range</h3>
        <div class="row">
          <div class="text-left col-sm-8">
            <p>
              The ESP8266 boards are much easier to set up in the Arduino IDE than the ESP32 range. If you don’t already have 
              it installed, download and install the IDE from here: 
              <a target="_blank" href="https://www.arduino.cc/en/main/software">https://www.arduino.cc/en/main/software</a> (don’t use the Web version).
            </p>

            <span class="instruction-number">1.</span>
            <p class="instruction">
              In the IDE, open the File Menu and choose Preferences and enter:
               <strong>http://arduino.esp8266.com/stable/package_esp8266com_index.json</strong> into the Additional Board Manager URLs field.
            </p>
          </div>

          <img class="col-sm-4 modal-image" v-bind:src="arduinoIde1" @click="showImage(arduinoIde1,arduinoIde1Title)">

        </div>
      </div>


      <ImageModal v-bind:selectedImageUrl="selectedImageUrl" v-bind:title="selectedImageTitle" />

    </div> <!-- /container -->
  </div>
</template>

<script>
// @ is an alias to /src
import ImageModal from '@/components/ImageModal.vue'
import imageBadge from '../assets/badge-image.jpg'
import arduinoIde1 from '../assets/add-library-url.jpg'
import JQuery from 'jquery'
let $ = JQuery

export default {
  name: 'home',
  data: function () {
    return {
      imageBadge,
      imageBadgeTitle: 'Setar YTE 2019 badge',
      arduinoIde1,
      arduinoIde1Title: 'Enter Additional Board Manager URL',
      selectedImageUrl: null,
      selectedImageTitle: null
    }
  },
  components: {
    ImageModal
  },
  created: function(){


  },
  mounted: function(){

  },
  methods: {
    showImage(imageUrl,title){
      this.selectedImageUrl = imageUrl;
      this.selectedImageTitle = title;
      if(imageUrl)
        $('#ImageModal').modal();
    }

  },
}
</script>


<style scoped lang="scss">
  .instruction-number{
    font-weight:700;
    font-size: 16px;
  }
  p.instruction{
    padding-left: 26px;
    display: inline-block;
    margin-top: -23px;
  }
</style>