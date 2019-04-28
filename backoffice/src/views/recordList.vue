<template>
    <div>
        <el-table
                :data="tableData.content"
                style="width: 100%">
            <el-table-column
                    prop="time"
                    label="时间">
            </el-table-column>
            <el-table-column
                    prop="num"
                    label="人数">
            </el-table-column>
        </el-table>
        <el-pagination
                background
                :total="tableData.totalElements"
                layout="total, prev, pager, next, jumper"
                @current-change="Page">
        </el-pagination>
    </div>
</template>

<script>
    export default {
        name: "record",
        data() {
            return {
                tableData: [],
            }
        },
        created: function () {
            this.axios.get('/record/page/0').then((response) => {
                this.tableData = response.data;
            })
        },
        methods: {
            Page(i) {
                this.axios.get('/record/page/' + (i-1)).then((response) => {
                    this.tableData = response.data;
                })
            }
        }
    }
</script>

<style scoped>

</style>
