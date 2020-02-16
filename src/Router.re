module Location = {
  type t;

  [@bs.get] external pathname: t => string = "pathname";
  [@bs.get] external search: t => string = "search";
  [@bs.get] external hash: t => string = "hash";
  [@bs.get] external key: t => string = "key";
};

module BrowserHistory = {
  type t;

  [@bs.get] external length: t => int = "length";
  [@bs.get] external action: t => string = "action";
  [@bs.get] external location: t => Location.t = "location";
  [@bs.send]
  external listen: (t, (Location.t, string) => unit) => (. unit) => unit =
    "listen";
  [@bs.send] external push: (t, string) => unit = "push";
  [@bs.send] external go: (t, int) => unit = "go";
  [@bs.send] external goBack: (t, int) => unit = "goBack";
};

module History = {
  type createBrowserHistoryOption = {
    basename: option(string),
    forceRefresh: option(bool),
    keyLength: option(int),
    getUserConfirmation: option((string, bool => unit)),
  };

  [@bs.module "history"]
  external createBrowserHistory:
    option(createBrowserHistoryOption) => BrowserHistory.t =
    "createBrowserHistory";
};

type mutations =
  | RouteChanged(string);

let current = ref(None);

let push = route => {
  switch (current^) {
  | Some(history) => BrowserHistory.push(history, route)
  | None => ()
  };
};

let createElement = (~basepath="/", ~children, ()) => {
  open Aim;

  let div = html("div");

  component(
    List.map(
      ((route, child)) =>
        div(
          [
            attr_("style", path =>
              path === route ? "" : "height:100%;display:none"
            ),
          ],
          [slot(child)],
        ),
      children,
    ),
    update => {
      let history =
        History.createBrowserHistory(
          Some({
            basename: Some(basepath),
            forceRefresh: None,
            keyLength: None,
            getUserConfirmation: None,
          }),
        );

      current := Some(history);

      let resolve = location => {
        let path = Location.pathname(location);

        let matched =
          List.find_opt(((route, _)) => route === path, children);

        switch (matched) {
        | Some(_) => update(path)
        | None => update("*")
        };
      };

      let unlisten =
        BrowserHistory.listen(
          history,
          (location, action) => {
            switch (action) {
            | "PUSH" => resolve(location)
            | "REPLACE" => resolve(location)
            | "POP" => resolve(location)
            | _ => ()
            };

            ();
          },
        );

      resolve(BrowserHistory.location(history));
      ();
    },
    (_, _, _) => {()},
  );
};
