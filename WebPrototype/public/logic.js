// Solo game — no authoritative server rules needed. The platform requires a code
// module at the archive root; this is the canonical solo stub.
export const meta = { game: "the-hollow-crown", minPlayers: 1, maxPlayers: 1 };
export function setup() { return {}; }
export function validateAction() { return { ok: true }; }
export function applyAction(state) { return state; }
export function isGameOver() { return { over: false }; }
export function viewFor(state) { return state; }
