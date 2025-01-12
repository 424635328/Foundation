<template>
  <div class="home">
    <div class="cat-list">
      <CatCard v-for="i in 24" :key="i" :catId="i"></CatCard>
    </div>
    <BackToTop />
  </div>
</template>

<script>
import CatCard from '../components/CatCard.vue';
import BackToTop from '../components/BackToTop.vue';

export default {
  name: 'HomePage', // 修改组件名称
  components: {
    CatCard,
    BackToTop
  }
}
</script>

<style scoped>
.home {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.cat-list {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  padding: 20px;
}
</style>