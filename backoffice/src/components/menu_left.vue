<template>
    <el-aside width="200px">
        <el-menu :default-openeds="['1','2']">
            <el-submenu index="1">
                <template slot="title"><i class="el-icon-tickets"></i>交通灯状态</template>
                <el-menu-item @click="go('/')" index="1">流量监控</el-menu-item>
                <el-menu-item @click="go('/remote')" index="2">远程控制</el-menu-item>
            </el-submenu>
            <el-submenu index="2">
                <template slot="title"><i class="el-icon-edit-outline"></i>用户管理</template>
                <el-menu-item index="1" @click="go('/user')">用户管理</el-menu-item>
                <el-menu-item index="2" @click="go('/user/add')">创建用户</el-menu-item>
                <el-menu-item index="3">
                    <a href="/logout">退出登陆</a>
                </el-menu-item>
            </el-submenu>
        </el-menu>
    </el-aside>
</template>

<script>
    export default {
        name: "menu_left",
        data() {
            return {user: ['action']}
        },
        created: function () {
            this.axios.get('/user/roles').then((response) => {
                this.user = response.data;
            })
        },
        methods: {
            hasRole(role) {
                for (var i = 0; i < this.user.length; i++) {
                    if (role === this.user[i]) return 1
                }
                return 0
            },
            alerthere(){
                this.$alert('您没有权限进行此项操作', '警告', {
                    confirmButtonText: '确定',
                });
            }
            ,
            go(url) {
                if (url === '/') {
                        this.$router.push(url)
                }
                if (url === '/remote') {
                    if(this.hasRole('action') || this.hasRole('admin')){
                        this.$router.push(url)
                    }else{this.alerthere()}
                }
                if (url === '/user') {
                    if(this.hasRole('user') || this.hasRole('admin')){
                        this.$router.push(url)
                    }else{this.alerthere()}
                }
                if (url === '/user/add') {
                    if(this.hasRole('add') || this.hasRole('admin')){
                        this.$router.push(url)
                    }else{this.alerthere()}
                }
            }
        }
    }
</script>

<style scoped>
    .el-aside {
        height: 650px;
        background-color: rgba(242, 242, 242, 0.7);
        box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .04)
    }
</style>
