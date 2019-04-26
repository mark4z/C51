<template>
    <el-form ref="form" :model="form" label-width="80px">
        <el-form-item label="用户名">
            <el-input v-model="form.username"></el-input>
        </el-form-item>
        <el-form-item label="密码">
            <el-input v-model="form.password"></el-input>
        </el-form-item>
        <el-form-item label="创建时间">
            <el-date-picker
                    v-model="form.time"
                    type="datetime"
                    placeholder="选择日期时间"
                    align="right"
                    :picker-options="pickerOptions1">
            </el-date-picker>
        </el-form-item>
        <el-form-item label="选择权限">
            <el-transfer :titles="['可用权限', '权限']" v-model="form.roles" :data="role_data"></el-transfer>
        </el-form-item>
        <el-form-item>
            <el-button type="primary" @click="onSubmit">立即创建</el-button>
            <el-button>取消</el-button>
        </el-form-item>
    </el-form>
</template>


<script>
    export default {
        name: "addUser",
        data() {
            return {
                form: {
                    username: '',
                    password: '',
                    time: '',
                    roles: [],
                },
                pickerOptions1: {
                    shortcuts: [{
                        text: '今天',
                        onClick(picker) {
                            picker.$emit('pick', new Date());
                        }
                    }, {
                        text: '昨天',
                        onClick(picker) {
                            const date = new Date();
                            date.setTime(date.getTime() - 3600 * 1000 * 24);
                            picker.$emit('pick', date);
                        }
                    }, {
                        text: '一周前',
                        onClick(picker) {
                            const date = new Date();
                            date.setTime(date.getTime() - 3600 * 1000 * 24 * 7);
                            picker.$emit('pick', date);
                        }
                    }]
                },
                role_data: [{
                    key: 'admin',
                    label: `管理员`,
                },
                    {
                        key: 'view',
                        label: `流量监控`,
                    }, {
                        key: 'action',
                        label: `远程控制`,
                    },
                    {
                        key: 'user',
                        label: `用户管理`,
                    },
                    {
                        key: 'add',
                        label: `创建用户`,
                    }],
            }
        },
        methods: {
            onSubmit() {
                var that = this;
                var roles = '';
                for (var i = 0; i < that.form.roles.length; i++) {
                    if (i == 0) {
                        roles += that.form.roles[i]
                    } else {
                        roles += ',' + that.form.roles[i]
                    }
                }
                this.$axios.post(
                    '/user/add',
                    this.qs.stringify({
                        username: that.form.username,
                        password: that.form.password,
                        roles: roles
                    }),
                ).then(() => {
                    const h = this.$createElement;
                    this.$notify({
                        title: '添加成功',
                        message: h('i', {style: 'color: teal'}, '添加用户' + that.form.username + '成功！')
                    });
                }).catch(() => {
                    const h = this.$createElement;
                    this.$notify({
                        title: '添加失败',
                        message: h('i', {style: 'color: teal'}, '添加用户' + that.form.username + '失败！用户已经存在')
                    });
                })
            }
        }
    }

</script>

<style scoped>

</style>
