<template>
    <div id="app">
        <el-container>
            <menu_left/>
            <el-main>
                <RouterView/>
            </el-main>
        </el-container>
    </div>
</template>

<script>
    import menu_left from "./components/menu_left"
    export default {
        name: 'app',
        components: {menu_left,}
    }
</script>

<style>
    #app {
        font-family: 'Avenir', Helvetica, Arial, sans-serif;
        -webkit-font-smoothing: antialiased;
        -moz-osx-font-smoothing: grayscale;
        color: #2c3e50;
        background-color: rgba(242, 242, 242, 0.7);
    }
</style>
