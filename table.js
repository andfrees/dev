// import request from '@/utils/request'

export function getList(params) {
  // console.log('getList')
  // return request({
  //   url: '/table/list',
  //   method: 'get',
  //   params
  // })

  return new Promise((resolve, reject) => {
    var num = Math.ceil(Math.random() * 10) // 生成1-10的随机数
    if (num) {
      const items = [{
        id: '@id',
        title: '@sentence(10, 20)',
        'status|1': ['published', 'draft', 'deleted'],
        author: 'name',
        display_time: '@datetime',
        pageviews: '@integer(300, 5000)'
      }]
      const userToken = {
        code: 20000,
        data: {
          total: items.length,
          items: items
        }
      }
      resolve(userToken)
    } else {
      console.log('num error')
      reject()
    }
  })
}
