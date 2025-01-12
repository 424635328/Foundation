const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  // 调整图片加载配置
  configureWebpack: {
    module: {
      rules: [
        {
          test: /\.(png|jpg|jpeg|gif|svg)$/i,
          use: [
            {
              loader: 'url-loader',
              options: {
                limit: 8192, // 设置图片内联的阈值，小于该阈值的图片会以 base64 编码内联
                name: 'static/img/[name].[hash:8].[ext]' // 设置输出图片的目录和命名规则
              }
            }
          ]
        }
      ]
    }
  }
})