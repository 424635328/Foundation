import { createRouter, createWebHistory } from 'vue-router'
import CatImage from '../components/CatImage.vue'
import CatDetail from '../components/CatDetail.vue'

const routes = [
  {
    path: '/',
    component: CatImage
  },
  {
    path: '/cat/:id',
    component: CatDetail,
    props: true
  }
]

const router = createRouter({
  history: createWebHistory(), // 使用 createWebHistory()
  routes
})

export default router