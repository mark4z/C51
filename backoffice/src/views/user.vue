<template>
    <div>
        <el-table
                :data="tableData"
                style="width: 100%">
            <el-table-column
                    prop="username"
                    label="用户名"
                    width="180">
            </el-table-column>
            <el-table-column
                    prop="time"
                    label="创建时间">
            </el-table-column>
            <el-table-column label="操作">
                <template slot-scope="scope">
                    <el-button
                            size="mini"
                            type="primary"
                            @click="handleEdit(scope.row.username)"
                            plain>编辑权限
                    </el-button>
                    <el-button
                            size="mini"
                            type="danger"
                            @click="handledelete(scope.row.username)"
                            plain>删除
                    </el-button>
                </template>
            </el-table-column>
        </el-table>
        <el-dialog
                title="提示"
                :visible.sync="dialogVisible"
                width="46%">
            <el-transfer :titles="['可用权限', '权限']" v-model="roles" :data="role_data"></el-transfer>
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="handleClose()">确 定</el-button>
        </el-dialog>
    </div>
</template>

<script>
    export default {
        name: "user",
        data() {
            return {
                tableData: [],
                dialogVisible: false,
                roles: [],
                now: '',
                role_data: [{
                    key: 'admin',
                    label: `管理员`,
                },
                    {
                        key: 'view',
                        label: `流量记录`,
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
        created: function () {
            this.axios.get('/user/all').then((response) => {
                this.tableData = response.data;
            })
        },
        methods: {
            handleEdit(id) {
                this.dialogVisible = true
                this.now = id
            },
            handleClose() {
                this.dialogVisible = false
                var that=this
                var roles = '';
                for (var i = 0; i < this.roles.length; i++) {
                    if (i == 0) {
                        roles += this.roles[i]
                    } else {
                        roles += ',' + this.roles[i]
                    }
                }
                this.$axios.post(
                    '/user/'+that.now+'/role',
                    this.qs.stringify({
                        role: roles
                    }),
                ).then(() => {
                    const h = this.$createElement;
                    this.$notify({
                        title: '操作成功',
                        message: h('i', {style: 'color: teal'}, '操作成功')
                    });
                })
            },
            handledelete(id) {
                this.axios.get('/user/' + id + '/delete').then(() => {
                    const h = this.$createElement;
                    this.$notify({
                        title: '删除成功',
                        message: h('i', {style: 'color: teal'}, '删除成功！')
                    });
                    this.axios.get('/user/all').then((response) => {
                        this.tableData = response.data;
                    })
                })
            },
        }
    }
</script>

<style scoped>

</style>
