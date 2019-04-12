<template>
  <div id="app">
    <!-- Fixed navbar -->
    <nav class="navbar navbar-inverse">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#">YTE Badge Documentation</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav navbar-right">
            <!-- <li><router-link to="/">Home</router-link></li> -->
            <!-- <li><router-link to="/about">About</router-link></li> -->
            <li><a href="https://github.com/setar-nv/youthtechevent">Back to GitHub repo</a></li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>
    <router-view/>
  </div>
</template>

<style lang="scss">
.navbar {
  a{
    font-weight: 600 !important;
    text-transform: uppercase !important;
    &:hover{
      color: #fff !important;
      text-decoration: underline !important;
    }
  }
}
.navbar-brand{
  pointer-events: none;
  font-weight: 500 !important;
  text-transform: none !important;
}
</style>
