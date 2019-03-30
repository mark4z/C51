<template>
    <div>
        <p>今日实时数据</p>
        <ve-line :data="chartData" :settings="chartSettings"></ve-line>
        <p>全部数据</p>
        <ve-line :data="chartData2" :settings="chartSettings"></ve-line>
    </div>
</template>

<script>
    export default {
        data() {
            this.chartSettings = {
                labelMap: {
                    num: '人流量',
                }
            }
            return {
                chartData: {
                    columns: ['time', 'num',],
                    rows: []
                },
                chartData2: {
                    columns: ['time', 'num',],
                    rows: []
                }
            }
        },
        methods: {
            today() {
                this.axios.get('/record/today').then((response) => {
                    this.chartData.rows = response.data;
                })
            }
        },
        created: function () {
            this.axios.get('/record/all').then((response) => {
                this.chartData2.rows = response.data;
            })
            this.axios.get('/record/today').then((response) => {
                this.chartData.rows = response.data;
            })
        },
        mounted: function () {
            this.$nextTick(function () {
                setInterval(this.today, 10000);
            })
        },
    }
</script>
