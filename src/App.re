[%bs.raw {|require('./app.css')|}];

let information: Typings.packageInfo = {
  name: "shade",
  version: "1.1.0",
  description: "Mathematically derived gradient explorer"
};

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) => <div> <Gradient appInfo=information /> </div>
};