import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose';
import { HydratedDocument } from 'mongoose';

export type Shoplists = HydratedDocument<Shoplist>;

@Schema()
export class Shoplist {
  @Prop({ required: true })
  bruker: string;

  @Prop({ required: true })
  komponent: string;

  @Prop({ required: true })
  antall: number;
}

export const ShoplistSchema = SchemaFactory.createForClass(Shoplist);
