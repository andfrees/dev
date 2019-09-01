// import request from '@/utils/request'

export function login(data) {
  // console.log('api/login')
  // console.log(data)
  // console.log('api/login return')
  // return request({
  //   url: '/user/login',
  //   method: 'post',
  //   data
  // })

  return new Promise((resolve, reject) => {
    var num = Math.ceil(Math.random() * 10) // 生成1-10的随机数
    if (num) {
      const userToken = {
        code: 20000,
        data: {
          token: 'admin-token'
        }
      }
      resolve(userToken)
    } else {
      console.log('num error')
      reject()
    }
  })
}

export function getInfo(token) {
  // console.log('api/getInfo')
  // console.log(token)
  // return request({
  //   url: '/user/info',
  //   method: 'get',
  //   params: { token }
  // })
  return new Promise((resolve, reject) => {
    var num = Math.ceil(Math.random() * 10) // 生成1-10的随机数
    if (num) {
      const userToken = {
        code: 20000,
        data: {
          'admin-token': {
            roles: ['admin'],
            introduction: 'I am a super administrator',
            avatar: 'https://wpimg.wallstcn.com/f778738c-e4f8-4870-b634-56703b4acafe.gif',
            name: 'Super Admin'
          }
        }
      }
      resolve(userToken)
    } else {
      console.log('num error')
      reject()
    }
  })
}

export function logout() {
  // console.log('api/logout')
  // return request({
  //   url: '/user/logout',
  //   method: 'post'
  // })

  return new Promise((resolve, reject) => {
    var num = Math.ceil(Math.random() * 10) // 生成1-10的随机数
    if (num) {
      const userToken = {
        code: 20000,
        data: 'success'
      }
      resolve(userToken)
    } else {
      console.log('num error')
      reject()
    }
  })
}
