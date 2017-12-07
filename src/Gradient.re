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

let linearGradient = (~angle: int, ~start: string, ~finish: string) =>
  Printf.sprintf("linear-gradient(%ddeg, %s, %s)", angle, start, finish);

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
    let gradient =
      linearGradient(~angle, ~start=gradientResult.start, ~finish=gradientResult.finish);
    <div>
      <Background gradient light=gradientResult.light appInfo />
      <div className="md-flex">
        <div className="md-col-6 lg-col-5 px2">
          <BaseColor base changeBase=(reduce((hex) => ChangeBase(hex))) />
        </div>
      </div>
    </div>
  }
};