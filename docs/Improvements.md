## Potential Improvements

We've wrote at length about the improvements we want to see with future
iterations of our ROV. After the judging and presenting process at the VJC
Science Fair, we've learnt many things about where the ROV can be further
developed. The wisdom we have gained are distilled below. 

The judge asked us what we could improve upon our ROV such that it can be
pitched to a government agency or a statuory board such as the Public Utilities
Board (PUB) to be used in our waters. 

These ROVs can be used for observation and for data collection, especially
because the conditions of the water can change drastically from one region to
another. Then the first question we have to ask ourselves is this: is our ROV
sea-worthy?

We have not given much consideration to the ROV's performance at extreme depths
and ranges. Heck, we didn't even consider it's performace due to it's center of
mass. To work on this, the first thing we have to do is find a mentor that is
willing to help us make a sea-worthy vehicle. 

This requires an in-depth understanding of hydrostatics and hydrodynamics, the
use of CAD software and advanced milling techniques to fabricate parts we need,
along with the software and mathematics to simulate the pressure on the various
parts of the hull. 

And this means we are moving from mere exploration, to engineering a product
that has to meet client, environmental and safety expectations. 

### Saltwater or freshwater?

The presence of a high concentration of electrolytes, means that we have more to
think about before building our ROV. Longevity of such a vehicle is a question,
due to factors such a corrosion that could happen on the boat. The brushless
motors we are using may malfunction due to the electrical conductivity of the
water. We may have to innovate and develop ways of potting and isolating our
electrical systems, something that is easier said than done. 

### Tether

The tether is the next big question on our list. This is because a tether is
literally the greatest range limitation if we are to deploy this to a reservoir.
Our 15m tether would eliminate much of its operating depth. However, radio waves
cannot penetrate through water as a medium. And because radio is the most common
choice of wireless transmission in other remotely operated vehicles, such as
drones, we have difficulties finding alternatives, which may be expensive and
hard to use.

Another problem we have with the tether, is what will happen when
our ROV fails. At this juncture, it is still possible to pull it out of the
water with the tether. Without this physical connection, we must come up with
subroutines that aid the recovery of the vessel, or the data collected by it, as
soon as a structural failure has been detected. 

The elimination of a tether and establishing wireless connectivity is a
difficult task, but will signify our ability to pitch the product to clients. 

### Camera
A camera will be a great improvement. This is what turns mere data collection into something truly remote with observation capabilities. However, if we do not have a tether, another challenge remains. We have no idea how to stream the camera feed from an underwater location. We could do something wireless and have the feed hosted on a nodejs webserver, but that would take more resources and expertise than I have at the current moment. 


### GPS and depth 
Here is something that I admit we've overlooked. In large water bodies, the
depth of the water is very important when discussing data collection. This is
because the amount of sunlight that reaches various depths will affect the organisms living and photosynthesizing at particular regions. This will play a large role in influencing the living conditions which have to be detected. 

As such, before we can talk about pitching our project as a serious engineering contender, we have to work on the robustness of basic navigation and longevity in harsh conditions.

### Industrial waterproofing
I hate to break it to you, but the fact of the matter is no one is going to buy
into the idea of a submarine being held together by acrylic and silicone rubber.
What would make the difference from here on is sadly money and expertise.
Eventually, we will have to move to more exotic and expensive materials instead
of mere acrylic. Our industrial design will have to be many times more
meticulous. 

### Control systems
We'll need to learn how to code system-critical software to actually run the
ROV. Eventually, this will have to be done reliably. Fat hope getting this
section done by the end of this year, this may take up to a few years to learn
enough before implementation.
