import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'

Vue.use(Router)

export default new Router({
    routes: [
        {
            path: '/',
            name: 'home',
            component: Home
        },
        {
            path: '/remote',
            name: 'Remote',
            component: () => import(/* webpackChunkName: "about" */ './views/Remote.vue')
        },
        {
            path: '/user',
            name: 'User',
            component: () => import(/* webpackChunkName: "about" */ './views/user.vue')
        },
        {
            path: '/user/add',
            name: 'Useradd',
            component: () => import(/* webpackChunkName: "about" */ './views/addUser.vue')
        },
        {
            path: '/record',
            name: 'record',
            component: () => import(/* webpackChunkName: "about" */ './views/recordList.vue')
        },
    ]
})
