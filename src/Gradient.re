type state = {
  base: string,
  angle: int,
  hueShift: int,
  saturate: float,
  lighten: float
};

type action =
  | ChangeBase(string)
  | ChangeHueShift(int)
  | ChangeSaturate(float)
  | ChangeLighten(float);

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
  initialState: () => {base: "#00ccff", saturate: 0., lighten: 0., hueShift: 130, angle: (-90)},
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
        <div className="flex-auto" />
        <form className="md-col-6 px2 py2">
          <fieldset className="fieldset-reset no-select">
            <legend className="h4 bold mb2"> (Utils.strEl("Gradient Spread")) </legend>
            <div className="sm-flex mxn2 no-select">
              <InputRange
                name="hue shift"
                min=(-180)
                max="180"
                value=(float_of_int(hueShift))
                labelBefore="Hue Shift"
                labelAfter="\176"
                onChange=(
                  reduce((evt) => ChangeHueShift(int_of_string(Utils.valueFromEvent(evt))))
                )
              />
              <InputRange
                name="saturate"
                min=(-1)
                max="1"
                step=0.01
                value=saturate
                labelBefore="Saturate"
                onChange=(
                  reduce((evt) => ChangeSaturate(float_of_string(Utils.valueFromEvent(evt))))
                )
              />
              <InputRange
                name="lighten"
                min=(-1)
                max="1"
                step=0.01
                value=lighten
                labelBefore="Lighten"
                onChange=(
                  reduce((evt) => ChangeLighten(float_of_string(Utils.valueFromEvent(evt))))
                )
              />
            </div>
          </fieldset>
        </form>
      </div>
    </div>
  }
};