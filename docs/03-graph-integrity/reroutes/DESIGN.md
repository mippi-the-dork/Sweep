# Reroute Chains — Design

**Sweep v1.0.0 · User guide**

## What Sweep treats as a reroute

Blueprint reroute nodes help route and organize wires, but they are not the final consumers of a value. **Distribute** follows them to the actual downstream input pins before deciding how many local Gets are needed.

## During Distribute

<!-- Final GIF: docs/assets/media/reroutes-demo.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="reroutes-demo">
  <img src="../../assets/media-placeholder.png" alt="Distribution follows reroutes to the consumers and removes only reroutes with no remaining live output." loading="lazy">
  <figcaption>Distribution follows reroutes to the consumers and removes only reroutes with no remaining live output.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a Get feeding two consumer calculations through a two-deep branched reroute chain. Distribute it, showing new Gets near both consumers and an unrelated still-live reroute remaining.</span></figcaption>
</figure>


Consider `Get Health → Reroute A → Reroute B → two separate calculations`. Sweep identifies the two calculation inputs, creates Gets near the destination nodes and reconnects them.

After the connection changes, some original reroutes may no longer lead anywhere. Sweep removes **only reachable reroutes whose outputs have become unused**. Reroutes that still serve another live connection should remain.

## During Consolidate

Consolidate does not simplify your reroute layout. It connects each selected Get's current outgoing wire paths to the one surviving Get, leaving the existing reroute chains in place.

## How to choose

If you want to **break up** a long rerouted shared wire, Distribute is appropriate. If you carefully arranged reroutes and want to **reuse one Get** without rearranging those paths, Consolidate is the better fit.

## Check afterward

Look for reroutes that should remain connected and confirm terminal consumers still receive the intended variable. Use Undo to restore the prior graph whenever the resulting presentation isn't useful.

---

For implementation, [read Technical](TECHNICAL.md).
