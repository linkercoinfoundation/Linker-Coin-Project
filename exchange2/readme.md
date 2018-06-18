# Standard Template

## First time
If this is the first time you initiate the project, you'll have to run either `npm install` or `yarn install` depending on the package manager you have installed in your system.

**Notice** that the project expect **Node v7.7.4** or higher. But its possible that you won't have any problems building from a previous version.

## Build
To initiate the build process, run `npm run build` on your terminal.

## Server
You can run `npm run serve` and this will build, start a server and open the app on your default browser.

This will:
- Compile the styles to css/style.css
- Copy the library.min.js and widgets.min.js files from their respective folders and copy them to the **js** directory

## Dev
You can run `npm run dev` to set up a live development server that will render style/widgets/library updates in real time. Before you do this though, you should do the following steps:

  1. Clone the APEX Library and run it in dev mode: `git clone git@github.com:alphapoint/APEX-Library.git && cd APEX-Library && npm install && npm run dev`
  1. Clone the APEX Widgets and run it in dev mode: `git clone git@github.com:alphapoint/APEX-Widgets.git && cd APEX-Widgets && npm install && npm run dev`

Now the libraries and widgets will be hosted on their own hot-reloading web servers and can be proxied into the live development server you create by running `npm run dev` in this repository. Now any changes made to styles, widgets or library will be instantly available.

## Standard Template Update - ^widgets@1.0.28
- Add bootstrap-grid.min.css to 'css/' and create a link tag in dashboard.html directory (can copy from v2templates/StandardUI/assets/css/standard/bootstrap-grid-min.css).
- Update css/yourstyle.css with:

``` 
/* widgets@1.0.10 */
.try-again-btn,
.confirm-close-btn {
  position: absolute;
  padding: 15px 22px;
  background: #0ea920;
  color: white;
  border-radius: 2px;
  border: 1px solid white;
  display: block;
  width: auto;
  text-align: center;
  margin: 0 auto;
  top: calc(50%);
  left: calc(50%);
  -webkit-transition: all .15s ease-in;
  -moz-transition: all .15s ease-in;
  transition: all .15s ease-in;
}

.try-again-btn {
  background: rgba(0, 89, 153, 0.816);
}

.try-again-btn:hover {
  background: #005999;
}

.confirm-close-btn:hover {
  background: #09981a;
}

.loader-container {
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  z-index: 9998;
  background: rgba(255, 255, 255, 0.5);
}

.loader-container-confirm {
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  z-index: 9998;
  background: rgb(255, 255, 255);
}

.loader {
  color: #82d1ff;
  font-size: 90px;
  text-indent: -9999em;
  z-index: 9999;
  overflow: hidden;
  width: 1em;
  height: 1em;
  border-radius: 50%;
  margin: 72px auto;
  position: relative;
  top: calc(50% - 1.5em);
  -webkit-transform: translateZ(0);
  -ms-transform: translateZ(0);
  transform: translateZ(0);
  -webkit-animation: load6 1.7s infinite ease, round 1.7s infinite ease;
  animation: load6 1.7s infinite ease, round 1.7s infinite ease;
}

@-webkit-keyframes load6 {
  0% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  5%,
  95% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  10%,
  59% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.087em -0.825em 0 -0.42em, -0.173em -0.812em 0 -0.44em, -0.256em -0.789em 0 -0.46em, -0.297em -0.775em 0 -0.477em;
  }
  20% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.338em -0.758em 0 -0.42em, -0.555em -0.617em 0 -0.44em, -0.671em -0.488em 0 -0.46em, -0.749em -0.34em 0 -0.477em;
  }
  38% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.377em -0.74em 0 -0.42em, -0.645em -0.522em 0 -0.44em, -0.775em -0.297em 0 -0.46em, -0.82em -0.09em 0 -0.477em;
  }
  100% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
}

@keyframes load6 {
  0% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  5%,
  95% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  10%,
  59% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.087em -0.825em 0 -0.42em, -0.173em -0.812em 0 -0.44em, -0.256em -0.789em 0 -0.46em, -0.297em -0.775em 0 -0.477em;
  }
  20% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.338em -0.758em 0 -0.42em, -0.555em -0.617em 0 -0.44em, -0.671em -0.488em 0 -0.46em, -0.749em -0.34em 0 -0.477em;
  }
  38% {
	box-shadow: 0 -0.83em 0 -0.4em, -0.377em -0.74em 0 -0.42em, -0.645em -0.522em 0 -0.44em, -0.775em -0.297em 0 -0.46em, -0.82em -0.09em 0 -0.477em;
  }
  100% {
	box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
}

@-webkit-keyframes round {
  0% {
	-webkit-transform: rotate(0deg);
	transform: rotate(0deg);
  }
  100% {
	-webkit-transform: rotate(360deg);
	transform: rotate(360deg);
  }
}

@keyframes round {
  0% {
	-webkit-transform: rotate(0deg);
	transform: rotate(0deg);
  }
  100% {
	-webkit-transform: rotate(360deg);
	transform: rotate(360deg);
  }
}

/* widgets@1.0.28 used with bootstrap-grid.min.css*/
.btn.dropdown-toggle {
  cursor: default;
  background: none !important;
  box-shadow: none !important
}

.btn.dropdown-toggle:hover,
.btn.dropdown-toggle:active,
.btn.dropdown-toggle:focus {
  color: white;
  box-shadow: none;
  top: 0;
  left: 0;
}

.btn.dropdown-toggle .caret {
  display: none;
}

.place-order-btn {
  position: absolute;
  top: 25%;
  left: 7.5%;
  width: 85%;
  height: 50%;
  border-radius: 0;
  margin-left: 0;
  text-align: center;
}

.place-order-btn:active,
.place-order-btn:focus {
  position: absolute;
  box-shadow: none !important;
  top: 25% !important;
  left: 7.5% !important;
}

.approximation-note {
  position: absolute;
  right: 5px;
  font-size: 11px;
}

.p-tb-15,
.p-lr-15 {
  padding-left: 15px;
  padding-right: 15px;
}

.input-lname {
  margin-right: 1rem;
}

.input-billingCity,
.input-middleName {
  display: none;
}

.input-verify {
  margin-top: 3rem;
}

.verify-explanation {
  white-space: pre-line;
  padding: 8px 16px;
}

.btm-195 {
  bottom: 195px !important;
}
.mt-neg35 {
  margin-top: -35px !important;
}

.modal-title-material-icon {
  vertical-align: middle;
  font-size: 29px;
}

/* widgets@1.0.31 */
.btm-195 {
  bottom: 195px !important;
}

.mt-neg35 {
  margin-top: -35px !important;
}

.modal-title-material-icon {
  vertical-align: middle;
  font-size: 29px;
}

/* widgets@1.0.39 */
.danger-bdr {
	border: 1px solid lightcoral
  }

/* widgets@1.0.59 */
.pika-single{z-index:9999;display:block;position:relative;color:#333;background:#fff;border:1px solid #ccc;border-bottom-color:#bbb;}.pika-single:after,.pika-single:before{content:" ";display:table}.pika-single:after{clear:both}.pika-single.is-hidden{display:none}.pika-single.is-bound{position:absolute;box-shadow:0 5px 15px -5px rgba(0,0,0,.5)}.pika-lendar{float:left;width:240px;margin:8px}.pika-title{position:relative;text-align:center}.pika-label{display:inline-block;position:relative;z-index:9999;overflow:hidden;margin:0;padding:5px 3px;font-size:14px;line-height:20px;font-weight:700;background-color:#fff}.pika-title select{cursor:pointer;position:absolute;z-index:9998;margin:0;left:0;top:5px;filter:alpha(opacity=0);opacity:0}.pika-next,.pika-prev{display:block;cursor:pointer;position:relative;outline:0;border:0;padding:0;width:20px;height:30px;text-indent:20px;white-space:nowrap;overflow:hidden;background-color:transparent;background-position:center center;background-repeat:no-repeat;background-size:75% 75%;opacity:.5}.pika-next:hover,.pika-prev:hover{opacity:1}.is-rtl .pika-next,.pika-prev{float:left;background-image:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABQAAAAeCAYAAAAsEj5rAAAAUklEQVR42u3VMQoAIBADQf8Pgj+OD9hG2CtONJB2ymQkKe0HbwAP0xucDiQWARITIDEBEnMgMQ8S8+AqBIl6kKgHiXqQqAeJepBo/z38J/U0uAHlaBkBl9I4GwAAAABJRU5ErkJggg==)}.is-rtl .pika-prev,.pika-next{float:right;background-image:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABQAAAAeCAYAAAAsEj5rAAAAU0lEQVR42u3VOwoAMAgE0dwfAnNjU26bYkBCFGwfiL9VVWoO+BJ4Gf3gtsEKKoFBNTCoCAYVwaAiGNQGMUHMkjGbgjk2mIONuXo0nC8XnCf1JXgArVIZAQh5TKYAAAAASUVORK5CYII=)}.pika-next.is-disabled,.pika-prev.is-disabled{cursor:default;opacity:.2}.is-disabled .pika-button,.is-outside-current-month .pika-button{opacity:.3;color:#999}.pika-select{display:inline-block}.pika-table{width:100%;border-collapse:collapse;border-spacing:0;border:0}.pika-table td,.pika-table th{width:14.285714285714286%;padding:0}.pika-table th{color:#999;font-size:12px;line-height:25px;font-weight:700;text-align:center}.pika-button{cursor:pointer;display:block;box-sizing:border-box;-moz-box-sizing:border-box;outline:0;border:0;margin:0;width:100%;padding:5px;color:#666;font-size:12px;line-height:15px;text-align:right;background:#f5f5f5}.is-disabled .pika-button,.is-selection-disabled{pointer-events:none;cursor:default}.pika-week{font-size:11px;color:#999}.is-today .pika-button{color:#3af;font-weight:700}.has-event .pika-button,.is-selected .pika-button{color:#fff;font-weight:700;background:#3af;box-shadow:inset 0 1px 3px #178fe5;border-radius:3px}.has-event .pika-button{background:#005da9;box-shadow:inset 0 1px 3px #0076c9}.is-disabled .pika-button,.is-inrange .pika-button{background:#D5E9F7}.is-startrange .pika-button{color:#fff;background:#6CB31D;box-shadow:none;border-radius:3px}.is-endrange .pika-button{color:#fff;background:#3af;box-shadow:none;border-radius:3px}.pika-button:hover,.pika-row.pick-whole-week:hover .pika-button{color:#fff;background:#ff8000;box-shadow:none;border-radius:3px}.pika-table abbr{border-bottom:none;cursor:help}

/* Widget@1.0.62 */
/* KYC Progress Bar */
.ap-modal_inner .ap-widget {
  background: transparent
}
.ap-modal_inner {
  background: #fff;
}
.progress-bar-container {
  width: 80%;
  margin: 0 auto;
  margin-left: 5%;
  display: inline-block;
}
.progressbar {
  counter-reset: step -1;
}
.progressbar li {
  list-style-type: none;
  width: 25%;
  float: left;
  font-size: 12px;
  position: relative;
  text-align: center;
  text-transform: uppercase;
  color: #7d7d7d;
}
.progressbar li:before {
  width: 30px;
  height: 30px;
  content: counter(step);
  counter-increment: step;
  line-height: 30px;
  border: 2px solid #7d7d7d;
  display: block;
  text-align: center;
  margin: 0 auto 10px auto;
  border-radius: 50%;
  background-color: white;
}
.progressbar li:after {
  width: 100%;
  height: 2px;
  content: '';
  position: absolute;
  background-color: #7d7d7d;
  top: 15px;
  left: -50%;
  z-index: -1;
}
.progressbar li:first-child:after {
  content: none;
}
.progressbar li.pass-level {
  color: green;
}
.progressbar li.pass-level:before {
  border-color: #55b776;
}
.progressbar li.pass-level + li:after {
  background-color: #55b776;
}

.progressbar li.under-review-level {
  color: #FFD700;
}
.progressbar li.under-review-level:before {
  border-color: #FEDD00;
}
.progressbar li.under-review-level + li:after {
  background-color: #FEDD00;
}

/* widets@1.0.65 */
/* ApInput Components */

 .ap-input-label {
   position: relative;
   width: 100%;
 }

 .datepicker-label-text,
 .label-text {
   font-size: 12px;
   position: absolute;
   width: 94%;
   top: 1px;
   left: 4px;
   overflow: hidden;
 }

 .ap-datepicker-input,
 .ap-input {
   display: block;
   width: 100%;
   height: 40px;
   line-height: 40px;
   padding-left: 4px;
   padding-top: 20px;
   font-size: 15px;
   letter-spacing: 1px;
 }

 .input-dob {
   position: relative;
 }

 .ap-datepicker-label {
   width: 100%
 }

 .datepicker-label-text {
   left: 17px;
 }

 .ap-select-input {
   font-size: 15px;
   height: 40px;
 }

 .select-label-text {
   position: absolute;
   left: 17px;
   top: -14px;
   font-size: 12px;
 }

 .ap-input-focused .ap-input {
   transition: .15s all linear;
   -o-transition: .15s all linear;
   -moz-transition: .15s all linear;
   -webkit-transition: .15s all linear;
 }

 .ap-input-focused .label-text {
  color: #3c7db6;
 }

 .ap-input-error {
   color: red;
   font-size: 11px;
   display: block;
   position: absolute;
   top:41px;
 }
```
