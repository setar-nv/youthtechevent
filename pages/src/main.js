import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
//window.$ = window.jQuery = require('jquery');
import 'bootstrap3'
//import 'bootstrap3/dist/css/bootstrap.min.css'
import './styling/bootstrap.custom.min.css'
import './styling/main.scss';

import imageViewer from "vue-image-viewer";
Vue.use(imageViewer);

Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
