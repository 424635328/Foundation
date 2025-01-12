<template>
    <div class="cat-card" @click="goToDetail(catId)">
      <img :src="`@/assets/images/catD/p${catId}.jpg`" alt="猫咪图片">
    </div>
  </template>
  
  <script>
  export default {
    props: {
      catId: {
        type: Number,
        required: true
      }
    },
    methods: {
      goToDetail(id) {
        this.$router.push(`/detail/${id}`);
      }
    }
  }
  </script>
  
  <style scoped>
  .cat-card {
    width: 200px;
    height: 200px;
    margin: 10px;
    cursor: pointer;
  }
  
  .cat-card img {
    width: 100%;
    height: 100%;
    object-fit: cover;
  }
  </style>