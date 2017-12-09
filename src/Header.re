open Helpers;

let component = ReasonReact.statelessComponent("Header");

let make = (~appInfo: Typings.packageInfo, _children) => {
  ...component,
  render: (_self) =>
    <header className="flex flex-center flex-wrap mxn2">
      <div className="flex-auto px2 mb2">
        <h1 className="m0">
          (appInfo.name |> text)
          <span className="h4"> (" v" ++ appInfo.version |> text) </span>
        </h1>
        <p className="m0"> (appInfo.description |> text) </p>
      </div>
    </header>
};