import Vue from 'vue'
import axios from  './plugins/axios'
import App from './App.vue'
import router from './router'
import './plugins/element.js'
import Qs from "qs"
import VCharts from 'v-charts'

Vue.config.productionTip = false
Vue.use(axios)
Vue.use(VCharts)

Vue.prototype.qs = Qs;

new Vue({
    router,
    render: h => h(App)
}).$mount('#app')
