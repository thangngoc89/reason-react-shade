open Helpers;

open Colorable;

type result('o, 'e) =
  | Ok('o)
  | Err('e);

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

let makeGradientCss = (~angle: float, ~start: string, ~finish: string) =>
  Printf.sprintf("linear-gradient(%sdeg, #%s, #%s)", Js.Float.toFixed(angle), start, finish);

let make = (~appInfo, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | ChangeBase(base) => ReasonReact.Update({...state, base})
    | ChangeAngle(angle) => ReasonReact.Update({...state, angle})
    | ChangeSaturate(saturate) => ReasonReact.Update({...state, saturate})
    | ChangeLighten(lighten) => ReasonReact.Update({...state, lighten})
    | ChangeHueShift(hueShift) => ReasonReact.Update({...state, hueShift})
    },
  /* let start =
     baseColor
     |> Converter.toHsl
     |> Manipulation.rotate(hueShift)
     |> Manipulation.saturate(saturate)
     |> Manipulation.lighten(lighten); */
  initialState: () => {base: "00ccff", saturate: 0., lighten: 0., hueShift: 130., angle: (-90.)},
  render: ({state: {base, saturate, lighten, hueShift, angle}, reduce}) => {
    let color = fromHex(base);
    switch color {
    | Ok(color) =>
      let light = Colorable.light(color);
      let start =
        color
        |> Colorable.rotate(hueShift)
        |> Colorable.saturate(saturate)
        |> Colorable.lighten(lighten)
        |> toHex;
      Js.log(
        color
        |> Colorable.rotate(hueShift)
        |> Colorable.saturate(saturate)
        |> Colorable.lighten(lighten)
      );
      let finish =
        color
        |> Colorable.rotate((-1.) *. hueShift)
        |> Colorable.desaturate(saturate)
        |> Colorable.darken(lighten)
        |> toHex;
      let gradient = makeGradientCss(~angle, ~start, ~finish);
      <div>
        <Background gradient light appInfo />
        <div className="md-flex">
          <div className="md-col-6 lg-col-5 px2">
            <FormBaseColor
              hexColor=base
              hslColor=(color |> toHsl)
              changeBase=(reduce((hex) => ChangeBase(hex)))
            />
          </div>
          <div className="flex-auto" />
          <FormGradientSpread
            angle
            changeAngle=(reduce((evt) => ChangeAngle(float_of_string(Utils.valueFromEvent(evt)))))
            hueShift
            changeHueShift=(
              reduce((evt) => ChangeHueShift(float_of_string(Utils.valueFromEvent(evt))))
            )
            saturate
            changeSaturate=(
              reduce((evt) => ChangeSaturate(float_of_string(Utils.valueFromEvent(evt))))
            )
            lighten
            changeLighten=(
              reduce((evt) => ChangeLighten(float_of_string(Utils.valueFromEvent(evt))))
            )
          />
        </div>
      </div>
    | Err(message) => <div> ("invalid result " ++ message |> text) </div>
    }
  }
};