type state = {
  base: string,
  angle: float,
  hueShift: float,
  saturate: float,
  lighten: float
};

type action =
  | ChangeBase(string)
  | ChangeAngle(float)
  | ChangeHueShift(float)
  | ChangeSaturate(float)
  | ChangeLighten(float);

let component = ReasonReact.reducerComponent("Gradient");

let linearGradient = (~angle: float, ~start: string, ~finish: string) =>
  Printf.sprintf("linear-gradient(%sdeg, %s, %s)", Js.Float.toFixed(angle), start, finish);

let make = (~appInfo, _children) => {
  let legendStyle = ReactDOMRe.Style.make(~lineHeight="2.25rem", ());
  {
    ...component,
    reducer: (action, state) =>
      switch action {
      | ChangeBase(base) => ReasonReact.Update({...state, base})
      | ChangeAngle(angle) => ReasonReact.Update({...state, angle})
      | ChangeSaturate(saturate) => ReasonReact.Update({...state, saturate})
      | ChangeLighten(lighten) => ReasonReact.Update({...state, lighten})
      | ChangeHueShift(hueShift) => ReasonReact.Update({...state, hueShift})
      },
    initialState: () => {base: "#00ccff", saturate: 0., lighten: 0., hueShift: 130., angle: (-90.)},
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
              <legend style=legendStyle className="h4 bold mb2">
                (Utils.strEl("Gradient Spread"))
              </legend>
              <div className="sm-flex mxn2 no-select">
                <InputRange
                  name="angle"
                  min=0
                  max="360"
                  value=angle
                  displayFixedValue=true
                  labelBefore="Angle"
                  labelAfter="\176"
                  onChange=(
                    reduce((evt) => ChangeAngle(float_of_string(Utils.valueFromEvent(evt))))
                  )
                />
                <InputRange
                  name="hue shift"
                  min=(-180)
                  max="180"
                  value=hueShift
                  displayFixedValue=true
                  labelBefore="Hue Shift"
                  labelAfter="\176"
                  onChange=(
                    reduce((evt) => ChangeHueShift(float_of_string(Utils.valueFromEvent(evt))))
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
  }
};