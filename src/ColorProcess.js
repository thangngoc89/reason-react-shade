import Color from "color"

export const gradient = function(base, hueShift, saturate, lighten) {
  let baseColor = Color(base)

  let from = baseColor
    .rotate(Number(hueShift))
    .saturate(saturate)
    .lighten(lighten)
    .hex()
  let to_ = baseColor
    .rotate(-1 * Number(hueShift))
    .desaturate(saturate)
    .darken(lighten)
    .hex()

  let light = baseColor.light()
  return { from, to_, light }
}

export const hsl = base =>
  Color(base)
    .hsl()
    .object()

export const hex_of_hsl = (h, s, l) => Color({ h, s, l }).hex()
export const hexToRgb = hex => {
  hex = hex.replace(/^#/, "")
  if (hex.length === 3) {
    hex = hex[0] + hex[0] + hex[1] + hex[1] + hex[2] + hex[2]
  }
  var num = parseInt(hex, 16)
  return { r: num >> 16, g: (num >> 8) & 255, b: num & 255 }
}
