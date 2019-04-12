<template>
<!-- Modal -->
  <div class="modal fade" id="ImageModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">

        <div class="modal-body">
          <img v-bind:src="selectedImageUrl"/>
          <p class="title"><small>{{title}}</small></p>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'ImageModal',
  props: ['selectedImageUrl', 'title'],
  data: function(){
    return {
      test: 'HW component',
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped lang="scss">
  #ImageModal{
    .modal-dialog{
      width: 80%;
      max-width: 1000px;
    }
    .title{
      margin-top: 10px;
      font-weight: 700;
      font-size: 18px;
      text-align: center;
    }

    /*==========  Mobile First Method  ==========*/

    /* Custom, iPhone Retina */ 
    @media only screen and (min-width : 320px) {

    }

    /* Extra Small Devices, Phones */ 
    @media only screen and (min-width : 480px) {

    }

    /* Small Devices, Tablets */
    @media only screen and (min-width : 768px) {
      #ImageModal{
        .modal-dialog{
          width: 100% !important;
         // max-width: 1000px;
        }
        .title{
          font-size: 12px;
        }
      }
    }

    /* Medium Devices, Desktops */
    @media only screen and (min-width : 992px) {

    }

    /* Large Devices, Wide Screens */
    @media only screen and (min-width : 1200px) {

    }
  }
</style>
