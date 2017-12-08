let component = ReasonReact.statelessComponent("BaseColor");

let floatValueFromEvent = (event) => event |> Utils.valueFromEvent |> float_of_string;

let make = (~base, ~changeBase, _children) => {
  ...component,
  render: (_self) => {
    let hslObject = Color.hsl(base);
    let h: float = hslObject##h;
    let s: float = hslObject##s;
    let l: float = hslObject##l;
    <form>
      <fieldset className="fieldset-reset py2">
        <div className="flex flex-center mb2">
          <label className="h4 bold flex-none mr2"> (Utils.strEl("Base Color")) </label>
          <input
            _type="text"
            value=base
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
            truncate=true
            labelBefore="Hue"
            labelAfter="\176"
            onChange=((evt) => changeBase(Color.hex_of_hsl(floatValueFromEvent(evt), s, l)))
          />
          <InputRange
            name="saturation"
            min=0
            max="100"
            value=s
            truncate=true
            labelBefore="Saturation"
            onChange=((evt) => changeBase(Color.hex_of_hsl(h, floatValueFromEvent(evt), l)))
          />
          <InputRange
            name="lightness"
            min=0
            max="100"
            value=l
            truncate=true
            labelBefore="Lightness"
            onChange=((evt) => changeBase(Color.hex_of_hsl(h, s, floatValueFromEvent(evt))))
          />
        </div>
      </fieldset>
    </form>
  }
};