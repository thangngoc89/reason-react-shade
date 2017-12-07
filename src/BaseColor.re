let component = ReasonReact.statelessComponent("BaseColor");

let make = (~base, _children) => {
  ...component,
  render: (_self) =>
    <form>
      <fieldset className="fieldset-reset py2">
        <div className="flex flex-center mb2">
          <label className="h4 bold flex-none mr2"> (Utils.strEl("Base Color")) </label>
          <input _type="text" className="m0 flex-auto field xfield-light" value=base />
        </div>
        <div className="sm-flex mxn2 no-select">
          <div className="flex-auto px2">
            <label className="h5 bold block"> (Utils.strEl("Hue")) </label>
            <input _type="range" min=0 max="360" className="col-12 dark-gray range-light" />
          </div>
          <div className="flex-auto px2">
            <label className="h5 bold block"> (Utils.strEl("Saturation")) </label>
            <input _type="range" min=0 max="100" className="col-12 dark-gray range-light" />
          </div>
          <div className="flex-auto px2">
            <label className="h5 bold block"> (Utils.strEl("Lightness")) </label>
            <input _type="range" min=0 max="100" className="col-12 dark-gray range-light" />
          </div>
        </div>
      </fieldset>
    </form>
};