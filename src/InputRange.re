let component = ReasonReact.statelessComponent("InputRange");

let make = (~name, ~min, ~max, ~value, ~labelBefore, ~labelAfter="", ~onChange, _children) => {
  ...component,
  render: (_self) =>
    <div className="flex-auto px2">
      <label className="h5 bold block">
        (Utils.strEl(labelBefore ++ " " ++ Utils.floatToString(value) ++ " " ++ labelAfter))
      </label>
      <input
        className="col-12 dark-gray range-light"
        name
        _type="range"
        onChange
        min
        max
        value=(Utils.floatToString(value))
      />
    </div>
};