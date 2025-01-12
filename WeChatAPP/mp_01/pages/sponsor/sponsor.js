Page({
  data: {
    selectedAmount: 0, // 选中的赞助金额
    qrcodeImages: {
      10: '/images/sponsor/qr.png',
      20: '/images/sponsor/qr.png',
      50: '/images/sponsor/qr.png',
    }, // 不同金额对应的收款码图片路径
    qrcodeImageUrl: '', // 当前显示的收款码图片路径
    customQrcodeUrl: '', // 自定义金额收款码图片路径
    showQRCode: false, // 是否显示收款码
    showCustomQRCode: false, // 是否显示自定义金额收款码
    showCustomInput: false, // 是否显示自定义金额输入框
    customAmount: 0, // 自定义金额
  },

  // 选择赞助金额
  selectAmount(e) {
    const amount = e.currentTarget.dataset.amount;
    if (amount === 'custom') {
      this.setData({
        selectedAmount: 0,
      });
    } else {
      this.setData({
        selectedAmount: parseInt(amount),
      });
    }
  },

  // 显示收款码
  showQRCode() {
    this.setData({
      showQRCode: true,
      showCustomInput: false,
      showCustomQRCode: false,
      qrcodeImageUrl: this.data.qrcodeImages[this.data.selectedAmount],
    });
  },

  // 显示自定义金额输入框
  showCustomInput() {
    this.setData({
      showQRCode: false,
      showCustomInput: true,
      showCustomQRCode: false,
    });
  },

  // 处理自定义金额输入
  onCustomInput(e) {
    this.setData({
      customAmount: e.detail.value,
    });
  },

  // 确认自定义金额
  confirmCustomAmount() {
      // 确认自定义金额
    const customAmount = parseFloat(this.data.customAmount);
    if (isNaN(customAmount) || customAmount <= 0) {
      wx.showToast({
        title: '请输入有效的金额',
        icon: 'none',
        duration: 2000,
      });
      return;
    }
    // 2. 保证金额小于等于2位小数
    const formattedAmount = customAmount.toFixed(2);

    
    // 2. 更新自定义金额收款码图片路径
    // 一个 API 接口可以根据金额生成收款码图片路径
    // 例如：`/api/generate_qrcode?amount=${customAmount}`
    wx.request({
    });
  
    this.setData({
      showCustomInput: false,
      showCustomQRCode: true,
      customQrcodeUrl: '../../images/sponsor/qr_self.png', // 替换为实际的自定义收款码图片路径
    });
  },

  // 进行赞助操作
  sponsor() {
    if (this.data.selectedAmount > 0) {
      this.showQRCode();
    } else {
      this.showCustomInput();
    }
  },
});