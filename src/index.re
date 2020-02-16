open Aim;
open Webapi.Dom;

let container = document |> Document.getElementById("app");
let container =
  switch (container) {
  | Some(root) => root
  | None =>
    exception RootElement_NotFound;
    raise(RootElement_NotFound);
  };

render(
  <Router> ("/", <Counter />) ("*", <NotFound />) </Router>,
  container,
);
