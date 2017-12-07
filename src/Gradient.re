type state = {
  base: string,
  saturate: int,
  lighten: int,
  hueShift: int,
  angle: int
};

type action =
  | ChangeBase(string)
  | ChangeSaturate(int)
  | ChangeLighten(int)
  | ChangeHueShift(int);

let component = ReasonReact.reducerComponent("Gradient");

let linearGradient = (~angle: int, ~from: string, ~to_: string) =>
  Printf.sprintf("linear-gradient(%ddeg, %s, %s)", angle, from, to_);

let make = (~appInfo, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | ChangeBase(base) => ReasonReact.Update({...state, base})
    | ChangeSaturate(saturate) => ReasonReact.Update({...state, saturate})
    | ChangeLighten(lighten) => ReasonReact.Update({...state, lighten})
    | ChangeHueShift(hueShift) => ReasonReact.Update({...state, hueShift})
    },
  initialState: () => {base: "#00ccff", saturate: 0, lighten: 0, hueShift: 130, angle: (-90)},
  render: ({state: {base, saturate, lighten, hueShift, angle}, reduce}) => {
    let gradientResult = Color.gradient(~base, ~hueShift, ~saturate, ~lighten);
    let from: string = gradientResult##from;
    let to_: string = gradientResult##to_;
    let light: bool = gradientResult##light;
    let gradient = linearGradient(~angle, ~from, ~to_);
    <div>
      <Background gradient light appInfo />
      <div className="md-flex">
        <div className="md-col-6 lg-col-5 px2">
          <BaseColor base changeBase=(reduce((evt) => ChangeBase(Utils.valueFromEvent(evt)))) />
        </div>
      </div>
    </div>
  }
};