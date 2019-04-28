<template>
    <el-form ref="form" :model="form" :rules="rules" label-width="80px">
        <el-form-item label="用户名" prop="username">
            <el-input v-model="form.username"></el-input>
        </el-form-item>
        <el-form-item label="密码" prop="password">
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
        <el-form-item label="选择权限" prop="roles">
            <el-transfer :titles="['可用权限', '权限']" v-model="form.roles" :data="role_data"></el-transfer>
        </el-form-item>
        <el-form-item>
            <el-button type="primary" @click="onSubmit('form')">立即创建</el-button>
            <el-button @click="go('/user')">取消</el-button>
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
                rules: {
                    username: [
                        {required: true, message: '请输入用户名', trigger: 'blur'},
                        {min: 3, max: 20, message: '长度在 3 到 20 个字符', trigger: 'blur'}
                    ],
                    password: [
                        {required: true, message: '请输入密码', trigger: 'blur'},
                        {min: 3, max: 20, message: '长度在 3 到 20 个字符', trigger: 'blur'}
                    ],
                    roles: [
                        {required: true, message: '请至少选择一个权限', trigger: 'change'},
                    ],
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
            onSubmit(form) {
                var that = this;
                this.$refs[form].validate((valid) => {
                    if (valid) {
                        var roles = '';
                        for (var i = 0; i < that.form.roles.length; i++) {
                            if (i == 0) {
                                roles += that.form.roles[i]
                            } else {
                                roles += ',' + that.form.roles[i]
                            }
                        }
                        const h = this.$createElement;
                        {
                            this.$axios.post(
                                '/user/add',
                                this.qs.stringify({
                                    username: that.form.username,
                                    password: that.form.password,
                                    roles: roles
                                }),
                            ).then(() => {
                                this.$notify({
                                    title: '添加成功',
                                    message: h('i', {style: 'color: teal'}, '添加用户' + that.form.username + '成功！')
                                });
                            }).catch(() => {
                                this.$notify({
                                    title: '添加失败',
                                    message: h('i', {style: 'color: teal'}, '添加用户' + that.form.username + '失败！用户已经存在')
                                });
                            })
                        }
                    } else {
                        that.$message.error("请更正以下错误！");
                        return false;
                    }
                });
            },
            go(url) {
                this.$router.push(url)
            }
        }
    }

</script>

<style scoped>

</style>
