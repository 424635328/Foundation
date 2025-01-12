<template>
  <div class="detail">
    <img :src="`./assets/images/catD/p${catId}.jpg`" alt="猫咪图片" />
  </div>
</template>

<script>
export default {
  name: 'DetailView', // 修改组件名称
  props: {
    catId: {
      type: Number,
      required: true
    }
  }
}
</script>

<style scoped>
.detail {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
}

.detail img {
  max-width: 100%;
  max-height: 100%;
}
</style>