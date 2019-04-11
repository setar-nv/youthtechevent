<template>
<!-- Modal -->
  <div class="modal fade" id="ImageModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">

        <div class="modal-body">
          <img v-bind:src="selectedImageUrl"/>
          <p><small>{{title}}</small></p>
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
  }
</style>
