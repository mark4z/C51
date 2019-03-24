<template>
  <div>
    <el-button type="primary" plain @click="flesh()">刷新</el-button>
    <ve-line :data="chartData"></ve-line>
  </div>
</template>

<script>
  export default {
    data () {
      return {
        chartData: {
          columns: ['time', 'num',],
          rows: []
        }
      }
    },
    methods:{
      flesh(){
        this.axios.get('/record/all').then((response) => {
          this.chartData.rows = response.data;
        })
      }
    },
    created: function () {
      this.axios.get('/record/all').then((response) => {
        this.chartData.rows = response.data;
      })
    },
  }
</script>
