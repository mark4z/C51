<template>
    <div class="Remote">
        <el-card class="box-card">
            <div slot="header" class="clearfix">
                <span>操作指南</span>
                <el-button style="float: right; padding: 3px 0" type="text">x</el-button>
            </div>
            <p>您可以在拥有对应权限的情况下任意调整智能交通灯的通行状态.</p>
            <p>步骤：</p>
            <p>（1）点击对应按钮</p>
            <p>（2）确认</p>
            <span class="el-icon-warning"></span>切换到正常模式以外的状态后，交通灯并不会自动重置，请在特殊情况结束后手动切换回正常模式
        </el-card>
        <p></p>
        <el-button type="success" @click="action('normal')">正常模式</el-button>
        <el-button type="warning" @click="action('ew')">东西通行</el-button>
        <el-button type="warning" @click="action('sn')">南北通行</el-button>
        <el-button type="danger" @click="action('stop')">紧急模式</el-button>
    </div>
</template>

<script>
    export default {
        name: "Remote",
        methods: {
            action(i) {
                this.$confirm('您确认要进行此操作?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                }).then(() => {
                    this.axios.get('/record/' + i)
                    this.$message({
                        type: 'success',
                        message: '切换成功!'
                    });
                }).catch(() => {
                    this.$message({
                        type: 'info',
                        message: '已取消'
                    });
                });
            }
        }
    }
</script>

<style scoped>

</style>
