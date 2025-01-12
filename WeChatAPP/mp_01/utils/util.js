//pages/utils/util.js
const formatTime = date => {
  const year = date.getFullYear()
  const month = date.getMonth() + 1
  const day = date.getDate()
  const hour = date.getHours()
  const minute = date.getMinutes()
  const second = date.getSeconds()

  return `${[year, month, day].map(formatNumber).join('/')} ${[hour, minute, second].map(formatNumber).join(':')}`
}

const formatNumber = n => {
  n = n.toString()
  return n[1] ? n : `0${n}`
}

module.exports = {
  formatTime
}


// 定义数据结构
const catDataSchema = {
  imageUrl: '', // 图片路径
  name: '', // 名字
  gender: '', // 性别
  age: '', // 年龄
  sterilization: '', // 绝育情况
  location: '', // 常驻地
  personality: '', // 性格
  features: '', // 特征
};

// 存储 catData 数据到本地
export const saveCatData = (catData) => {
  wx.setStorageSync('catData', catData);
}

// 从本地读取 catData 数据
export const getCatData = () => {
  return wx.getStorageSync('catData');
}

// 更新 catData 数据
export const updateCatData = (newCatData) => {
  const currentData = wx.getStorageSync('catData');
  const updatedData = { ...currentData, ...newCatData };
  wx.setStorageSync('catData', updatedData);
}



const catData = require('../pages/common/catData.js'); 
// 添加新的猫数据，并追加到已有数据数组中

export const addCatData = (newCatData) => {
  // 获取已有数据
  let existingCatData = wx.getStorageSync('catData');

  // 如果本地缓存中没有数据，则初始化为空数组
  if (!existingCatData) {
      existingCatData = [];
  }

  // 将新数据添加到已有数据的数组中
  existingCatData.push(newCatData);

  // 保存更新后的数据到本地缓存
  wx.setStorageSync('catData', existingCatData);
};


