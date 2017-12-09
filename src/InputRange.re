open Helpers;

let component = ReasonReact.statelessComponent("InputRange");

let make =
    (
      ~name,
      ~min,
      ~max,
      ~value,
      ~displayFixedValue=false,
      ~labelBefore,
      ~labelAfter="",
      ~onChange,
      ~step=1.0,
      _children
    ) => {
  ...component,
  render: (_self) => {
    let computedValue = displayFixedValue ? Js.Float.toFixed(value) : Js.Float.toString(value);
    <div className="flex-auto px2">
      <label className="h5 bold block">
        ({j|$labelBefore $computedValue $labelAfter|j} |> text)
      </label>
      <input
        className="col-12 dark-gray range-light"
        name
        _type="range"
        onChange
        min
        max
        step
        value=(Js.Float.toString(value))
      />
    </div>
  }
};