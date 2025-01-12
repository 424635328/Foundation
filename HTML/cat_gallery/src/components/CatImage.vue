<template>
  <div class="cat-gallery">
    <div v-for="(index, i) in 24" :key="index" class="cat-image" :style="{ order: i % 4 }" v-lazy="getImagePath(index)"
      @click="goToCatDetail(index)">
      <img :src="getImagePath(index)" alt="一只可爱的猫咪">
    </div>
    <button class="back-to-top" @click="scrollToTop" v-if="showButton">
      回到顶部
    </button>
  </div>
</template>

<script>
export default {
  name: 'CatImage',
  data() {
    return {
      preloadedImages: [], // 预加载图片数组
      showButton: false // 回到顶部按钮是否显示
    }
  },
  mounted() {
    // 预加载图片
    this.preloadImages();
    // 监听滚动事件
    window.addEventListener('scroll', this.handleScroll);
  },
  beforeDestroy() {
    // 移除滚动事件监听
    window.removeEventListener('scroll', this.handleScroll);
  },
  methods: {
    getImagePath(index) {
      return require(`@/assets/images/catD/p${index}.jpg`);
    },
    preloadImages() {
      for (let i = 1; i <= 24; i++) {
        const img = new Image();
        img.src = this.getImagePath(i);
        this.preloadedImages.push(img);
      }
    },
    handleScroll() {
      // 当滚动距离超过 100 像素时显示按钮
      this.showButton = window.pageYOffset > 100;
    },
    scrollToTop() {
      // 滚动到页面顶部
      window.scrollTo({
        top: 0,
        behavior: 'smooth' // 设置滚动动画
      });
    },
    goToCatDetail(index) {
      this.$router.push({
        path: '/cat/' + index // 将猫咪 ID 传递给路由
      });
    }
  }
}
</script>

<style scoped>
.cat-gallery {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
}

.cat-image {
  width: 200px;
  margin: 10px;
  position: relative;
  /* 为占位符设置定位 */
  cursor: pointer;
  /* 设置鼠标点击样式 */
}

.cat-image img {
  width: 100%;
  border-radius: 8px;
  transition: opacity 0.3s ease;
  /* 添加过渡效果 */
}

.cat-image .placeholder {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: #f5f5f5;
  /* 设置占位符背景色 */
  border-radius: 8px;
}

.cat-gallery>div {
  /* 调整图片顺序 */
  flex-basis: 25%;
  /* 每个图片占25%宽度 */
}

.back-to-top {
  position: fixed;
  bottom: 20px;
  right: 20px;
  padding: 10px 20px;
  background-color: #4CAF50;
  /* 按钮背景色 */
  color: white;
  border: none;
  border-radius: 5px;
  cursor: pointer;
}
</style>