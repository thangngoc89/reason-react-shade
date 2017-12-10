open Helpers;

let component = ReasonReact.statelessComponent("FormGradientSpread");

let legendStyle = ReactDOMRe.Style.make(~lineHeight="2.25rem", ());

let make =
    (
      ~angle,
      ~changeAngle,
      ~hueShift,
      ~changeHueShift,
      ~saturate,
      ~changeSaturate,
      ~lighten,
      ~changeLighten,
      _children
    ) => {
  ...component,
  render: (_self) =>
    <form className="md-col-6 px2 py2">
      <fieldset className="fieldset-reset no-select">
        <legend style=legendStyle className="h4 bold mb2"> ("Gradient Spread" |> text) </legend>
        <div className="sm-flex mxn2 no-select">
          <InputRange
            name="angle"
            min=(-180)
            max="180"
            value=angle
            displayFixedValue=true
            labelBefore="Angle"
            labelAfter="\176"
            onChange=changeAngle
          />
          <InputRange
            name="hue shift"
            min=(-180)
            max="180"
            value=hueShift
            displayFixedValue=true
            labelBefore="Hue Shift"
            labelAfter="\176"
            onChange=changeHueShift
          />
          <InputRange
            name="saturate"
            min=(-1)
            max="1"
            step=0.01
            value=saturate
            labelBefore="Saturate"
            onChange=changeSaturate
          />
          <InputRange
            name="lighten"
            min=(-1)
            max="1"
            step=0.01
            value=lighten
            labelBefore="Lighten"
            onChange=changeLighten
          />
        </div>
      </fieldset>
    </form>
};