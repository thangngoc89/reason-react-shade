type state = {
  h: float,
  s: float,
  l: float
};

type action =
  | UpdateHsl;

let component = ReasonReact.reducerComponent("BaseColor");

let floatValueFromEvent = (event) => event |> Utils.valueFromEvent |> float_of_string;

let make = (~base, ~changeBase, ~changeBaseStr, _children) => {
  ...component,
  initialState: () => {h: 0., s: 0., l: 0.},
  reducer: (action, _) =>
    switch action {
    | UpdateHsl =>
      let hslObject = Color.hsl(base);
      let h: float = hslObject##h;
      let s: float = hslObject##s;
      let l: float = hslObject##l;
      ReasonReact.Update({h, s, l})
    },
  didMount: (self) => {
    self.reduce((_) => UpdateHsl, ());
    ReasonReact.NoUpdate
  },
  render: ({state, reduce}) => {
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
            onChange=changeBase
          />
        </div>
        <div className="sm-flex mxn2 no-select">
          <InputRange
            name="hue"
            min=0
            max="360"
            value=h
            labelBefore="Hue"
            labelAfter="&deg;"
            onChange=(
              reduce((evt) => changeBaseStr(Color.hex_of_hsl(floatValueFromEvent(evt), s, l)))
            )
          />
        </div>
      </fieldset>
    </form>
    /* <InputRange
         name="saturation"
         min=0
         max="100"
         value=s
         labelBefore="Saturation"
         onChange=(reduce((evt) => changeBaseStr(h, floatValueFromEvent(evt), l)))
       />
       <InputRange
         name="lightness"
         min=0
         max="100"
         value=l
         labelBefore="Lightness"
         onChange=(reduce((evt) => changeBaseStr(h, s, floatValueFromEvent(evt))))
       /> */
  }
};