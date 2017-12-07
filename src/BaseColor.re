type state = {
  h: float,
  s: float,
  l: float
};

type action =
  | ChangeHue(float)
  | ChangeSaturation(float)
  | ChangeLightness(float)
  | UpdateHsl;

let component = ReasonReact.reducerComponent("BaseColor");

let make = (~base, ~changeBase, _children) => {
  ...component,
  initialState: () => {h: 0.0, s: 0.0, l: 0.0},
  reducer: (action, state) =>
    switch action {
    | ChangeHue(h) => ReasonReact.Update({...state, h})
    | ChangeSaturation(s) => ReasonReact.Update({...state, s})
    | ChangeLightness(l) => ReasonReact.Update({...state, l})
    | UpdateHsl =>
      let hslObject = Color.hsl(base);
      let h: float = hslObject##h;
      let s: float = hslObject##s;
      let l: float = hslObject##l;
      Js.log("called update hsl");
      ReasonReact.Update({h, s, l})
    },
  didMount: (self) => {
    self.reduce((_) => UpdateHsl, ());
    ReasonReact.NoUpdate
  },
  render: ({state: {h, s, l}, reduce}) =>
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
            onChange=(reduce((evt) => ChangeHue(float_of_string(Utils.valueFromEvent(evt)))))
          />
          <InputRange
            name="saturation"
            min=0
            max="100"
            value=s
            labelBefore="Saturation"
            onChange=(
              reduce((evt) => ChangeSaturation(float_of_string(Utils.valueFromEvent(evt))))
            )
          />
          <InputRange
            name="lightness"
            min=0
            max="100"
            value=l
            labelBefore="Lightness"
            onChange=(reduce((evt) => ChangeLightness(float_of_string(Utils.valueFromEvent(evt)))))
          />
        </div>
      </fieldset>
    </form>
};