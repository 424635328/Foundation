<template>
    <div>
      <h1>猫咪详情</h1>
      <img :src="getImagePath" alt="猫咪图片">
      <!-- 其他猫咪信息 -->
    </div>
  </template>
  
  <script>
  export default {
    name: 'CatDetail',
    props: {
      catId: Number // 获取从路由传递过来的猫咪 ID
    },
    computed: {
      getImagePath() {
        return require(`@/assets/images/catD/p${this.catId}.jpg`);
      }
    }
  };
  </script>