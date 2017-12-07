let component = ReasonReact.statelessComponent("Header");

let make = (~appInfo: Typings.packageInfo, _children) => {
  ...component,
  render: (_self) =>
    <header className="flex flex-center flex-wrap mxn2">
      <div className="flex-auto px2 mb2">
        <h1 className="m0">
          (Utils.strEl(appInfo.name))
          <span className="h4"> (Utils.strEl(" v" ++ appInfo.version)) </span>
        </h1>
        <p className="m0"> (Utils.strEl(appInfo.description)) </p>
      </div>
    </header>
};