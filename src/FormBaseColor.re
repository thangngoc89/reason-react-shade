open Helpers;

let component = ReasonReact.statelessComponent("BaseColor");

let floatValueFromEvent = (event) => event |> Utils.valueFromEvent |> float_of_string;

let make = (~hexColor, ~hslColor, ~changeBase, _children) => {
  ...component,
  render: (_self) => {
    let (h, s, l) = hslColor;
    <form>
      <fieldset className="fieldset-reset py2">
        <div className="flex flex-center mb2">
          <label className="h4 bold flex-none mr2"> ("Base Color" |> text) </label>
          <input
            _type="text"
            value=hexColor
            className="m0 flex-auto field xfield-light"
            onChange=((evt) => changeBase(Utils.valueFromEvent(evt)))
          />
        </div>
        <div className="sm-flex mxn2 no-select">
          <InputRange
            name="hue"
            min=0
            max="360"
            value=h
            displayFixedValue=true
            labelBefore="Hue"
            labelAfter="\176"
            onChange=((evt) => changeBase(Color.hex_of_hsl(floatValueFromEvent(evt), s, l)))
          />
          <InputRange
            name="saturation"
            min=0
            max="100"
            value=s
            displayFixedValue=true
            labelBefore="Saturation"
            onChange=((evt) => changeBase(Color.hex_of_hsl(h, floatValueFromEvent(evt), l)))
          />
          <InputRange
            name="lightness"
            min=0
            max="100"
            value=l
            displayFixedValue=true
            labelBefore="Lightness"
            onChange=((evt) => changeBase(Color.hex_of_hsl(h, s, floatValueFromEvent(evt))))
          />
        </div>
      </fieldset>
    </form>
  }
};