<template>
    <button @click="scrollToTop" v-if="showButton">
      回到顶部
    </button>
  </template>
  
  <script>
  export default {
    data() {
      return {
        showButton: false
      }
    },
    mounted() {
      window.addEventListener('scroll', this.handleScroll);
    },
    // 更改为 beforeUnmount
    beforeUnmount() {
      window.removeEventListener('scroll', this.handleScroll);
    },
    methods: {
      handleScroll() {
        this.showButton = window.pageYOffset > 100;
      },
      scrollToTop() {
        window.scrollTo({
          top: 0,
          behavior: 'smooth'
        });
      }
    }
  }
  </script>
  
  <style scoped>
  button {
    position: fixed;
    bottom: 20px;
    right: 20px;
    padding: 10px 20px;
    background-color: #4CAF50;
    color: white;
    border: none;
    cursor: pointer;
  }
  </style>