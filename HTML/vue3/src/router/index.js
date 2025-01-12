import { createRouter, createWebHistory } from 'vue-router'
import HomePage from '../views/HomePage.vue' // 修改导入路径
import DetailView from '../views/DetailView.vue' // 修改导入路径

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomePage // 修改组件名称
    },
    {
      path: '/detail/:catId',
      name: 'detail',
      component: DetailView, // 修改组件名称
      props: true
    }
  ]
})

export default router